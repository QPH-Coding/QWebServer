// Author: QPH-Coding
// Create: 2022/9/26
// File: server.cc
// License: Apache 2.0

#include "server.h"

void QWebServer::EventLoop() {
  int listen_socket_fd = net::TcpSocket();
  // TODO temp port: 8090
  sockaddr_in server_address = net::SocketAddress4(AF_INET, 8090, INADDR_ANY);
  net::SetReuseAddress(listen_socket_fd, true);
  net::Bind(listen_socket_fd, server_address);
  net::Listen(listen_socket_fd, 5);

  epoll_listener_.AddReadEvent(listen_socket_fd);
  while (true) {
    std::vector<epoll_event> epoll_events = epoll_listener_.GetEpollReadyEvents();
    for (auto &epoll_event : epoll_events) {
      if (epoll_event.data.fd == listen_socket_fd) {
        std::shared_ptr<Client> sp_client = net::Accept(listen_socket_fd);
        sub_reactor_read_.Enqueue(sp_client);
        // TODO time wheel use
      }
    }
  }
}