// author: qph-coding
// Create: 2022/9/29
// File: http_connection.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
#define QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_

#include "../encapsulation/net.h"
#include "http_request.h"
#include "http_response.h"

// en:
// the task of the server deal with
// notice http_request() and http_response() will return a reference
// this will improve efficiency, and can modify the request and response store in HttpConnection
// zh:
// 服务器处理的工作
// 注意http_request()和http_response()返回的是个引用
// 这会提高效率，同时也能直接修改HttpConnection里面的request和response
class HttpConnection {
 public:
  // en: the SubReactor read/write will depend on this status
  // zh: SubReactor的读写将会取决于这个status
  enum class Status {
    Wait, Read, Write
  };

  explicit HttpConnection(Client client) noexcept;
  const Client &get_client() noexcept;
  const Status &get_status() const noexcept;
  void set_start_time() noexcept;
  const timeval &get_start_time() const noexcept;
  void set_status(Status status) noexcept;
  HttpRequest &http_request() noexcept;
  HttpResponse &http_response() noexcept;
 private:
  Status status_;
  timeval start_time_;
  Client client_;
  HttpRequest http_request_;
  HttpResponse http_response_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
