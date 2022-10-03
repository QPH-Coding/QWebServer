// Author: QPH-Coding
// Create: 2022/10/2
// File: http_request.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_REQUEST_H_
#define QWEBSERVER_SRC_HTTP_HTTP_REQUEST_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <regex>
#include "json.h"
#include <iostream>
#include "http_request_head.h"

class HttpRequest {
 public:
  // en: now the server only support 3 methods
  // zh: 现在服务器只支持三种方法
  enum class Method {
    GET, POST, DELETE
  };
  using http_request_head = HttpRequestHead::http_request_head;
  explicit HttpRequest(const std::string &raw_request_) noexcept;

  Method get_method() const noexcept;
  std::string get_url() const noexcept;
  std::string get_protocol() const noexcept;
  std::string get_request_body() const noexcept;
  std::string get_head(const http_request_head &head_key) const noexcept;
  bool is_effective() const noexcept;
 private:
  void Analyze(const std::string &raw_request_) noexcept;

  inline static bool JudgeFormat(
      const std::sregex_token_iterator &lhs,
      const std::sregex_token_iterator &rhs) noexcept;

  bool is_effective_;
  // en: request line
  // zh: 请求行
  Method method_;
  std::string url_;
  std::string protocol_version_;
  // en: request head
  // zh: 请求头
  Json::Value request_head_;
  // en: request body
  // zh: 请求实体
  std::string request_body_;

  static const std::regex split_line_regex_;
  static const std::regex split_head_body_regex_;
  static const std::regex space_regex_;
  static const std::regex colon_regex_;
};

#endif //QWEBSERVER_SRC_HTTP_HTTP_REQUEST_H_
