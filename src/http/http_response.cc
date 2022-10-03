// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response.cc
// License: Apache 2.0

#include "http_response.h"

void HttpResponse::set_protocol_version(const std::string &protocol_version) noexcept {
  protocol_version_ = protocol_version;
}

void HttpResponse::set_status(const http_response_status &status) noexcept {
  status_ = status;
}

void HttpResponse::add_head(const std::pair<http_response_head, std::string> &head) noexcept {
  response_head_.push_back(head);
}

void HttpResponse::add_head(const http_response_head &key, const std::string &value) noexcept {
  response_head_.emplace_back(key, value);
}

void HttpResponse::set_response_body(const std::string &request_body) noexcept {
  response_body_ = request_body;
}
std::string HttpResponse::to_string() const noexcept {
  std::string http_response_string;
  http_response_string += protocol_version_ + " "
      + std::to_string(status_.first) + " "
      + status_.second + "\r\n";
  for (auto &head : response_head_) {
    http_response_string += head.first + ": " + head.second + "\r\n";
  }
  http_response_string += "\r\n";
  http_response_string += response_body_;
  return http_response_string;
}
void HttpResponse::add_wait_send_file(const std::string &file_path) noexcept {
  wait_send_file_.push_back(file_path);
}
std::vector<std::string> HttpResponse::get_wait_send_file() const noexcept {
  return wait_send_file_;
}
