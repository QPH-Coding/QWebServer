// Author: QPH-Coding
// Create: 2022/9/26
// File: server.cc
// License: Apache 2.0

#include "server.h"

void QWebServer::EventLoop() {
  listen_socket_fd_ = net::TcpSocket();
  sockaddr_in server_address = net::SocketAddress4(AF_INET, Config::Port(), INADDR_ANY);
  // en: reuse port, easy to restart the server
  // zh: 端口复用，能够方便重启服务器
  net::SetReuseAddress(listen_socket_fd_);
  net::Bind(listen_socket_fd_, server_address);
  net::Listen(listen_socket_fd_, 5);

  epoll_listener_.AddReadEvent(listen_socket_fd_);
  while (true) {
    std::vector<epoll_event> epoll_events = epoll_listener_.GetEpollReadyEvents();
    for (auto &epoll_event : epoll_events) {
      if (epoll_event.data.fd == listen_socket_fd_) {
        while (true) {
          std::shared_ptr<Client> sp_client = net::Accept(listen_socket_fd_);
          if (!sp_client) {
            break;
          }
          AsyncLog4Q_Info("Accept connection from " + sp_client->get_address_port());
          epoll_listener_.AddReadEvent(sp_client->get_fd());
          fd_ip_map_[sp_client->get_fd()] = sp_client->get_address_port();
          AsyncLog4Q_Info(sp_client->get_address_port() + " use fd: " + std::to_string(sp_client->get_fd()));
        }
      } else if (epoll_event.events & EPOLLIN) {
        int client_fd = epoll_event.data.fd;
        sub_reactor_read_.Enqueue(std::make_shared<Client>(client_fd, fd_ip_map_[client_fd]));
      }
    }
  }
}
QWebServer::QWebServer() noexcept
    : epoll_listener_(EpollListener(1000)),
      sub_reactor_read_(Config::SubReactorNum(), 1000, SubReactorReadFunc, this),
      sub_reactor_write_(Config::SubReactorNum(), 1000, SubReactorWriteFunc, this),
      service_(Config::ThreadNum(), 1000, ServiceFunc, this),
      mysql_conn_pool_(Config::MySqlInitNum(), mysql_deal::ConstructConnection, mysql_deal::DestructConnection) {
  signal(SIGPIPE, SIG_IGN);
  sub_reactor_read_.Start();
  AsyncLog4Q_Info("SubReadReactor init successfully.");
  service_.Start();
  AsyncLog4Q_Info("Service init successfully.");
  sub_reactor_write_.Start();
  AsyncLog4Q_Info("SubWriteReactor init successfully.");
  time_wheel_.Start();
  AsyncLog4Q_Info("TimeWheel init successfully.");
}

void QWebServer::SubReactorReadFunc(std::shared_ptr<Client> &sp_client, void *arg) {
  AsyncLog4Q_Info(
      "Server will read socket_fd: "
          + std::to_string(sp_client->get_fd())
          + " from " + sp_client->get_address_port());
  auto p_server = static_cast<QWebServer *>(arg);
  std::string raw_request;
  if (file::ReadNonblockFile(sp_client->get_fd(), raw_request)) {
    // TEST: output request
//    std::cout << raw_request << std::endl;
    std::shared_ptr<HttpConnection> sp_http_connection(new HttpConnection(*sp_client, raw_request));
    // en: if request head 'Connection' is not keep-alive, just close the fd
    // zh: 如果请求头中的'Connection'不是keep-alive，读取完所有东西后可以直接关闭fd
    if (sp_http_connection->get_http_request().get_head(HttpRequestHead::Connection) == "keep-alive") {
      p_server->time_wheel_.add(sp_client->get_fd());
    } else {
      close(sp_client->get_fd());
    }
    p_server->service_.Enqueue(sp_http_connection);
  }
}

void QWebServer::SubReactorWriteFunc(std::shared_ptr<HttpResponse> &sp_http_response, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
  if (file::WriteSocket(
      sp_http_response->get_client_socket_fd(),
      sp_http_response->get_response_header(),
      sp_http_response->get_response_body())) {
    AsyncLog4Q_Info("Response " + p_server->fd_ip_map_[sp_http_response->get_client_socket_fd()] + " successfully.");
  } else {
    AsyncLog4Q_Warn("Response " + p_server->fd_ip_map_[sp_http_response->get_client_socket_fd()] + " failed.");
  }
}

void QWebServer::ServiceFunc(std::shared_ptr<HttpConnection> &sp_http_connection, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
  std::shared_ptr<HttpResponse> sp_http_response = http_service::DealWithRequest(
      sp_http_connection->get_http_request(), &p_server->mysql_conn_pool_);
  sp_http_response->set_client_socket_fd(sp_http_connection->get_client().get_fd());
  p_server->sub_reactor_write_.Enqueue(sp_http_response);
  // TEST: output response
//  std::cout << sp_http_response->get_response_header() << std::endl;
}
QWebServer::~QWebServer() noexcept {
  close(listen_socket_fd_);
  time_wheel_.Close();
}
