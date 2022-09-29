// Author: QPH-Coding
// Create: 2022/9/26
// File: net.cc
// License: Apache 2.0

#include "net.h"

Client::Client(int fd, const sockaddr_in &address) noexcept
    : fd_(fd),
      address_(address) {}

int Client::GetFd() const { return fd_; }

sockaddr_in Client::GetAddress() const { return address_; }

int net::TcpSocket() {
  int res = socket(PF_INET, SOCK_STREAM, 0);
  if (res == -1) {
    std::cout << "TcpSocket init failed" << std::endl;
    exit(101);
  }
  return res;
}

int net::UdpSocket() {
  int res = socket(PF_INET, SOCK_DGRAM, 0);
  if (res == -1) {
    std::cout << "UdpSocket init failed" << std::endl;
    exit(101);
  }
  return res;
}

sockaddr_in net::SocketAddress4(int domain, int port, in_addr_t address) {
  sockaddr_in ip_address_4{};
  bzero(&ip_address_4, sizeof(ip_address_4));
  ip_address_4.sin_family = domain;
  ip_address_4.sin_port = htons(port);
  ip_address_4.sin_addr.s_addr = address;
  return ip_address_4;
}

void net::SetReuseAddress(int socket_fd, bool enable) {
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(bool));
}

void net::Bind(int socket_fd, sockaddr_in socket_address) {
  int res = bind(socket_fd, (sockaddr *) &socket_address, sizeof(socket_address));
  if (res == -1) {
    std::cout << "Bind socket failed." << std::endl;
    exit(102);
  }
}

void net::Listen(int socket_fd, int backlog) {
  int res = listen(socket_fd, backlog);
  if (res == -1) {
    std::cout << "Listen socket failed." << std::endl;
    exit(103);
  }
}

Client net::Accept(int socket_fd) {
  sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int fd = accept(socket_fd, (sockaddr *) &client_address, &client_address_len);
  return {fd, client_address};
}
