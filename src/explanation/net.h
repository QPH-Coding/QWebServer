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

class Client {
 public:
  Client(int fd, const sockaddr_in &address) noexcept;
  int GetFd() const;
  sockaddr_in GetAddress() const;
 private:
  int fd_;
  sockaddr_in address_;
};

namespace net {
int TcpSocket();
int UdpSocket();
sockaddr_in SocketAddress4(int domain, int port, in_addr_t address);
void SetReuseAddress(int socket_fd, bool enable);
void Bind(int socket_fd, sockaddr_in socket_address);
void Listen(int socket_fd, int backlog);
Client Accept(int socket_fd);
}  // namespace net
#endif  // WEBSERVER_NET_H
