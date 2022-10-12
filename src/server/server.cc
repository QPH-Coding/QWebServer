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
        // en:
        // while many client connect to the server
        // because the epoll is ET mode
        // we must use while call accept
        // until it wrong
        // zh:
        // 当很多连接同时连接到服务器时
        // 因为epoll使用的是ET模式
        // 我们必须使用while去调用accept
        // 知道他出错
        while (true) {
          Client client = net::Accept(listen_socket_fd_);
          if (client.get_fd() == -1) {
            break;
          }
          epoll_listener_.AddReadEvent(client.get_fd());
          fd_conn_map_[client.get_fd()] = std::make_shared<HttpConnection>(client);
          AsyncLog4Q_Debug("Connect " + client.get_address_port() + " fd:" +
              std::to_string(client.get_fd()));
        }
      } else if (epoll_event.events & EPOLLIN) {
        int client_fd = epoll_event.data.fd;
        fd_conn_map_[client_fd]->set_status(HttpConnection::Status::Read);
        sub_reactor_pool_.Enqueue(fd_conn_map_[client_fd]);
      } else if (epoll_event.events & EPOLLOUT) {
        int client_fd = epoll_event.data.fd;
        fd_conn_map_[client_fd]->set_status(HttpConnection::Status::Write);
        AsyncLog4Q_Debug(
            "Epoll Write fd:" + std::to_string(client_fd) + " "
                + fd_conn_map_[client_fd]->get_client().get_address_port());
        sub_reactor_pool_.Enqueue(fd_conn_map_[client_fd]);
      }
    }
  }
}
QWebServer::QWebServer() noexcept
    : epoll_listener_(EpollListener(10000)),
      sub_reactor_pool_(Config::SubReactorNum(), 10000, &SubReactorFunc, this),
      service_pool_(Config::ThreadNum(), 10000, &ServiceFunc, this),
      mysql_conn_pool_(Config::MySqlInitNum(), mysql_deal::ConstructConnection, mysql_deal::DestructConnection) {}

void QWebServer::Start() {
  sub_reactor_pool_.Start();
  AsyncLog4Q_Info("SubReactor init and start success.");
  service_pool_.Start();
  AsyncLog4Q_Info("Service init and start success.");
  time_wheel_.Start();
  AsyncLog4Q_Info("TimeWheel init and start success.");

  EventLoop();
}

void QWebServer::SubReactorFunc(std::shared_ptr<HttpConnection> &sp_http_connection, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
  if (sp_http_connection->get_status() == HttpConnection::Status::Read) {
    SubReactorRead(sp_http_connection, p_server);
  } else if (sp_http_connection->get_status() == HttpConnection::Status::Write) {
    SubReactorWrite(sp_http_connection, p_server);
  }
}

void QWebServer::SubReactorRead(std::shared_ptr<HttpConnection> &sp_http_connection, QWebServer *p_server) {
  AsyncLog4Q_Debug(
      "Server will read socket_fd: "
          + std::to_string(sp_http_connection->get_client().get_fd())
          + " from " + sp_http_connection->get_client().get_address_port());
  sp_http_connection->set_start_time();
  std::string raw_request;
  if (file::ReadNonblockFile(sp_http_connection->get_client().get_fd(), raw_request)) {
    // TEST: output request
//    std::cout << raw_request << std::endl;
    sp_http_connection->http_request().Analyze(raw_request);
    // en:
    // if request head 'Connection' is not keep-alive
    // don't add to TimeWheel and close the fd after writing
    // zh:
    // 如果请求头中的'Connection'不是keep-alive
    // 不要将它加入时间轮，并且在写入完成后关闭fd
    if (sp_http_connection->http_request().get_head(HttpRequestHead::Connection) == "keep-alive") {
      p_server->time_wheel_.add(sp_http_connection->get_client().get_fd());
    }
    // example:     Request /login 192.168.3.4:53386 31
    // description: Request uri client-ip:port fd
    AsyncLog4Q_Info("Request " +
        sp_http_connection->http_request().get_url() + " " +
        sp_http_connection->get_client().get_address_port() + " " +
        std::to_string(sp_http_connection->get_client().get_fd()));
    p_server->service_pool_.Enqueue(sp_http_connection);
  }
}

void QWebServer::SubReactorWrite(std::shared_ptr<HttpConnection> &sp_http_connection, QWebServer *p_server) {
  AsyncLog4Q_Debug(
      "Write fd:" + std::to_string(sp_http_connection->get_client().get_fd()) + " "
          + sp_http_connection->get_client().get_address_port());
  int socket_fd = sp_http_connection->get_client().get_fd();
  if (!sp_http_connection->http_response().is_have_write_head()) {
    AsyncLog4Q_Debug("Write fd:" + std::to_string(socket_fd) + " response head.");
    std::vector<char> response_header = sp_http_connection->http_response().get_response_header();
    long header_index = file::WriteSocket(socket_fd, response_header);
    sp_http_connection->http_response().append_header_index(header_index);
    if (header_index == response_header.size()) {
      sp_http_connection->http_response().set_have_write_head();
      AsyncLog4Q_Debug("Finish write fd:" + std::to_string(socket_fd) + " response head.");
    }
  }
  std::vector<char> response_body = sp_http_connection->http_response().get_response_body();
  long body_index = file::WriteSocket(socket_fd, response_body);
  if (body_index < 0) {
    // en:
    // here write failed, probably get a SIGPIPE
    // and should not append index, or will get a SIGSEGV
    // zh:
    // 这里写入失败的话，很有可能是收到了一个SIGPIPE
    // 不要移动索引index，不然可能会有段错误
    return;
  }
  if (body_index == response_body.size()) {
    timeval start = sp_http_connection->get_start_time();
    timeval end{};
    gettimeofday(&end, nullptr);
    double return_time = static_cast<double >(end.tv_sec) - static_cast<double >(start.tv_sec)
        + ((static_cast<double >(end.tv_usec) - static_cast<double >(start.tv_usec)) / 1000000);
    // example:     Response 200 /login 0.001141s 192.168.3.4:53386 31
    // description: Response status-code uri return-time client-ip:port fd
    AsyncLog4Q_Info(
        "Response " +
            std::to_string(sp_http_connection->http_response().get_response_status().first) + " " +
            sp_http_connection->http_request().get_url() + " " +
            std::to_string(return_time) + "s " +
            sp_http_connection->get_client().get_address_port() + " " +
            std::to_string(sp_http_connection->get_client().get_fd()));
    p_server->epoll_listener_.ModWriteToReadEvent(socket_fd);
    if (sp_http_connection->http_request().get_head(HttpRequestHead::Connection) != "keep-alive") {
      // en:
      // If the connection is not keep-alive, TimeWheel didn't add fd
      // after write and response, should close this fd
      // zh:
      // 如果连接不是keep-alive的，时间轮之前不会将它加入其中
      // 在写入并响应完成后，应该要关掉这个fd
      close(socket_fd);
      AsyncLog4Q_Debug("Close the fd: " + std::to_string(socket_fd));
    }
  } else if (body_index <= 0) {
    AsyncLog4Q_Warn("Response " + sp_http_connection->get_client().get_address_port() + " in "
                        + std::to_string(socket_fd) + " failed.");
  }
  AsyncLog4Q_Debug("Write fd:" + std::to_string(socket_fd) + " " + std::to_string(body_index));
  sp_http_connection->http_response().append_body_index(body_index);
}

void QWebServer::ServiceFunc(std::shared_ptr<HttpConnection> &sp_http_connection, void *arg) {
  auto p_server = static_cast<QWebServer *>(arg);
  sp_http_connection->http_response() =
      std::move(http_service::DealWithRequest(sp_http_connection->http_request(), &p_server->mysql_conn_pool_));
  // en:
  // register the epoll write event to
  // make the sub reactor get write message
  // zh:
  // 通过注册epoll写事件
  // 让sub reactor收到写的通知
  p_server->epoll_listener_.ModReadToWriteEvent(sp_http_connection->get_client().get_fd());
}
QWebServer::~QWebServer() noexcept {
  close(listen_socket_fd_);
  time_wheel_.Close();
}
