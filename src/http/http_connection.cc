// Author: QPH-Coding
// Create: 2022/9/29
// File: http_connection.cc
// License: Apache 2.0

#include "http_connection.h"
HttpConnection::HttpConnection(const int client_fd, const std::string &raw_string) noexcept
    : client_fd_(client_fd), http_request_(raw_string) {}

int HttpConnection::get_client_fd() const noexcept {
  return client_fd_;
}

HttpRequest HttpConnection::get_http_request() const noexcept {
  return http_request_;
}
