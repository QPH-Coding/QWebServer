// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_
#define QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_

#include <string>
#include <vector>
#include <regex>
#include <sys/mman.h>
#include "http_response_status.h"
#include "http_response_head.h"
#include "../encapsulation/file.h"
#include "../log/async_log4q.h"

// TODO this class design can be optimized
class HttpResponse {
 public:
  using http_response_status = HttpResponseStatus::http_response_status;
  using http_response_head = HttpResponseHead::http_response_head;
  static const std::unordered_map<std::string, std::string> content_type;
  HttpResponse() = default;

  void set_protocol_version(const std::string &protocol_version = "HTTP/1.1") noexcept;
  void set_status(const http_response_status &status) noexcept;
  void add_head(const std::pair<http_response_head, std::string> &head) noexcept;
  void add_head(const http_response_head &key, const std::string &value) noexcept;
  void set_response_body(const char *response_body,
                         long whole_file_size,
                         long start_index = 0,
                         long end_index = -1) noexcept;

  bool add_file(const std::string &file_path, long start_index = 0, long end_index = -1) noexcept;
  const http_response_status& get_response_status() noexcept;
  std::vector<char> get_response_header() const noexcept;
  void set_have_write_head() noexcept;
  bool is_have_write_head() const noexcept;
  std::vector<char> get_response_body();
  void append_body_index(long body_index) noexcept;
  void append_header_index(long header_index) noexcept;
 private:
  // en: response line
  // zh: 响应行
  std::string protocol_version_;
  http_response_status status_;
  // en: response head
  // zh: 响应头
  std::vector<std::pair<http_response_head, std::string>> response_head_;
  long header_index_ = 0;
  bool have_write_head_ = false;
  // en: response body
  // zh: 响应实体
  std::vector<char> response_body_;
  long body_index_ = 0;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_H_
