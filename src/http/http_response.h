// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_
#define QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_

#include <string>
#include <vector>
#include "http_response_status.h"
#include "http_response_head.h"
#include "../explanation/file.h"

// TODO this class design can be optimized
class HttpResponse {
 public:
  using http_response_status = HttpResponseStatus::http_response_status;
  using http_response_head = HttpResponseHead::http_response_head;
  HttpResponse() = default;

  void set_protocol_version(const std::string &protocol_version) noexcept;
  void set_status(const http_response_status &status) noexcept;
  void add_head(const std::pair<http_response_head, std::string> &head) noexcept;
  void add_head(const http_response_head &key, const std::string &value) noexcept;
  void set_response_body(const std::string &response_body) noexcept;

  void set_client_socket_fd(int client_socket_fd) noexcept;
  void set_client_ip_port(const std::string& client_ip_port) noexcept;
  void add_wait_send_file(const std::string &file_path) noexcept;
  int get_client_socket_fd() const noexcept;
  std::string get_client_ip_port() const noexcept;
  std::vector<std::string> get_wait_send_file() const noexcept;
  std::string to_string() const noexcept;
 private:
  // en: response line
  // zh: 响应行
  std::string protocol_version_;
  http_response_status status_;
  // en: response head
  // zh: 响应头
  std::vector<std::pair<http_response_head, std::string>> response_head_;
  // en: response body
  // zh: 响应实体
  std::string response_body_;

  std::vector<std::string> wait_send_file_;
  int client_socket_fd_;
  std::string client_ip_port_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_
