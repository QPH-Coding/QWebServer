// Author: QPH-Coding
// Create: 2022/9/29
// File: http_connection.cc
// License: Apache 2.0

#include "http_connection.h"
HttpConnection::HttpConnection(const Client &client_fd, const std::string &raw_string) noexcept
    : client_(client_fd), http_request_(raw_string) {}

Client HttpConnection::get_client() const noexcept {
  return client_;
}

HttpRequest HttpConnection::get_http_request() const noexcept {
  return http_request_;
}
