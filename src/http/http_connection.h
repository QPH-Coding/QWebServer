// author: qph-coding
// Create: 2022/9/29
// File: http_connection.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
#define QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_

#include "../explanation/net.h"
#include "http_request.h"
#include "http_response.h"

class HttpConnection {
 public:
  explicit HttpConnection(Client client) noexcept;
  const Client &get_client() noexcept;
  HttpRequest &http_request() noexcept;
  HttpResponse &http_response() noexcept;
 private:
  Client client_;
  HttpRequest http_request_;
  HttpResponse http_response_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
