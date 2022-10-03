// Author: QPH-Coding
// Create: 2022/9/19
// File: net.h
// License: Apache 2.0

#ifndef WEBSERVER_NET_H
#define WEBSERVER_NET_H
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <memory>
#include "../log/async_log4q.h"

class Client {
 public:
  Client(int fd, std::string address_port) noexcept;
  int get_fd() const;
  std::string get_address_port() const;
 private:
  int fd_;
  std::string address_port_;
};

namespace net {
int TcpSocket();
int UdpSocket();
sockaddr_in SocketAddress4(int domain, int port, in_addr_t address);
void SetReuseAddress(int socket_fd);
void Bind(int socket_fd, sockaddr_in socket_address);
void Listen(int socket_fd, int backlog);
std::shared_ptr<Client> Accept(int socket_fd);
}  // namespace net
#endif  // WEBSERVER_NET_H
