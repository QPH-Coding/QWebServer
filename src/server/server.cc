// Author: QPH-Coding
// Create: 2022/9/26
// File: server.cc
// License: Apache 2.0

#include "server.h"

const int QWebServer::MaxBufferSize = 1024;

void QWebServer::EventLoop() {
  listen_socket_fd_ = net::TcpSocket();
  // TODO temp port: 8090
  sockaddr_in server_address = net::SocketAddress4(AF_INET, 8090, INADDR_ANY);
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
        std::shared_ptr<Client> sp_client = net::Accept(listen_socket_fd_);
        AsyncLog4Q_Info("Accept connection from " + sp_client->get_address_port());
        epoll_listener_.AddReadEvent(sp_client->get_fd());
        time_wheel_.add(sp_client->get_fd());
      } else if (epoll_event.events & EPOLLIN) {
        int client_fd = epoll_event.data.fd;
        sub_reactor_read_.Enqueue(std::make_shared<int>(client_fd));
      }
    }
  }
}
QWebServer::QWebServer() noexcept
    : epoll_listener_(EpollListener(1000)),
      sub_reactor_read_(2, 1000, SubReactorReadFunc, this),
      sub_reactor_write_(2, 1000, SubReactorWriteFunc, this),
      service_(4, 1000, ServiceFunc, this) {
  sub_reactor_read_.Start();
  service_.Start();
  sub_reactor_write_.Start();
}

void QWebServer::SubReactorReadFunc(std::shared_ptr<int> &sp_client_fd, void *arg) {
  AsyncLog4Q_Info("Server will read from socket_fd: " + std::to_string(*sp_client_fd));
  auto p_server = static_cast<QWebServer *>(arg);
  char buffer[MaxBufferSize];
  std::string raw_request;
  while (true) {
    memset(buffer, '\0', MaxBufferSize);
    int have_read = recv(*sp_client_fd, buffer, sizeof(buffer), 0);
    if (have_read <= 0) {
      std::shared_ptr<HttpConnection> sp_http_connection(new HttpConnection(*sp_client_fd, raw_request));
//      p_server->service_.Enqueue(sp_http_connection);
      std::cout << "raw request:" << std::endl;
      std::cout << raw_request << std::endl;
      break;
    } else {
      raw_request += buffer;
    }
  }
}

void QWebServer::SubReactorWriteFunc(std::shared_ptr<HttpResponse> &sp_http_response, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
}

void QWebServer::ServiceFunc(std::shared_ptr<HttpConnection> &sp_http_connection, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
  std::cout << sp_http_connection->get_http_request().get_protocol() << " "
            << sp_http_connection->get_http_request().get_url()
            << std::endl;
}
QWebServer::~QWebServer() noexcept {
  close(listen_socket_fd_);
}
