// Author: QPH-Coding
// Create: 2022/9/29
// File: http_connection.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
#define QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_

#include "../explanation/net.h"
#include "http_request.h"

class HttpConnection {
 public:
  HttpConnection(const int client_fd, const std::string &raw_string) noexcept;
  int get_client_fd() const noexcept;
  HttpRequest get_http_request() const noexcept;
 private:
  int client_fd_;
  HttpRequest http_request_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
