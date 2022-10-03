// Author: QPH-Coding
// Create: 2022/9/26
// File: net.cc
// License: Apache 2.0

#include "net.h"

#include <memory>
#include <utility>

Client::Client(int fd, std::string address_port) noexcept
    : fd_(fd),
      address_port_(std::move(address_port)) {}

int Client::get_fd() const { return fd_; }

std::string Client::get_address_port() const { return address_port_; }

int net::TcpSocket() {
  int res = socket(PF_INET, SOCK_STREAM, 0);
  if (res == -1) {
    AsyncLog4Q_Error("Init tcp socket failed.");
    exit(1);
  }
  AsyncLog4Q_Info("Init tcp socket successfully.");
  return res;
}

int net::UdpSocket() {
  int res = socket(PF_INET, SOCK_DGRAM, 0);
  if (res == -1) {
    AsyncLog4Q_Error("Init udp socket failed.");
    exit(1);
  }
  AsyncLog4Q_Info("Init udp socket successfully.");
  return res;
}

sockaddr_in net::SocketAddress4(int domain, int port, in_addr_t address) {
  sockaddr_in ip_address_4{};
  bzero(&ip_address_4, sizeof(ip_address_4));
  ip_address_4.sin_family = domain;
  ip_address_4.sin_port = htons(port);
  ip_address_4.sin_addr.s_addr = htonl(address);
  return ip_address_4;
}

void net::SetReuseAddress(int socket_fd) {
  int enable = 1;
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
  AsyncLog4Q_Info("Server set reuse address successfully.");
}

void net::Bind(int socket_fd, sockaddr_in socket_address) {
  int res = bind(socket_fd, (sockaddr *) &socket_address, sizeof(socket_address));
  if (res < 0) {
    AsyncLog4Q_Error("Server socket bind failed.");
    exit(1);
  }
  AsyncLog4Q_Info("Server socket bind successfully.");
}

void net::Listen(int socket_fd, int backlog) {
  int res = listen(socket_fd, backlog);
  if (res == -1) {
    AsyncLog4Q_Error("Server listen socket failed.");
    exit(1);
  }
  AsyncLog4Q_Info("Server listen socket successfully.");
}

std::shared_ptr<Client> net::Accept(int socket_fd) {
  sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int fd = accept(socket_fd, (sockaddr *) &client_address, &client_address_len);
  char *client_ip;
  inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
  int client_port = ntohs(client_address.sin_port);
  std::string client_address_port = client_ip;
  client_address_port += +":" + std::to_string(client_port);
  return std::make_shared<Client>(fd, client_address_port);
}
