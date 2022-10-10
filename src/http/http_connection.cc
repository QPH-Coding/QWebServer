// Author: QPH-Coding
// Create: 2022/9/29
// File: http_connection.cc
// License: Apache 2.0

#include "http_connection.h"
const Client &HttpConnection::get_client() noexcept {
  return client_;
}

HttpRequest &HttpConnection::http_request() noexcept {
  return http_request_;
}
HttpResponse &HttpConnection::http_response() noexcept {
  return http_response_;
}
HttpConnection::HttpConnection(Client client) noexcept
    : client_(std::move(client)) {}
