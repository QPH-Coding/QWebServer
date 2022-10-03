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
  HttpConnection(const Client &client_fd, const std::string &raw_string) noexcept;
  Client get_client() const noexcept;
  HttpRequest get_http_request() const noexcept;
 private:
  Client client_;
  HttpRequest http_request_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
