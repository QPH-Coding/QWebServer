// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response.cc
// License: Apache 2.0

#include "http_response.h"

const std::unordered_map<std::string, std::string> HttpResponse::content_type = {
    {".html", "text/html"},
    {".xml", "text/xml"},
    {".xhtml", "application/xhtml+xml"},
    {".txt", "text/plain"},
    {".rtf", "application/rtf"},
    {".pdf", "application/pdf"},
    {".word", "application/nsword"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".au", "audio/basic"},
    {".mpeg", "video/mpeg"},
    {".mpg", "video/mpeg"},
    {".avi", "video/x-msvideo"},
    {".gz", "application/x-gzip"},
    {".tar", "application/x-tar"},
    {".css", "text/css "},
    {".js", "text/javascript "},
};

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

void HttpResponse::set_response_body(const std::string &response_body) noexcept {
  response_body_ = response_body;
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
void HttpResponse::add_file(const std::string &file_path) noexcept {
  FILE *file_fd = fopen(file_path.c_str(), "r");
  std::string response_body = file::ReadNonblockFile(file_fd);
  set_response_body(response_body);
  // en: add content-type header by suffix automatically
  // zh: 自动添加content-type头根据文件后缀
  std::regex dot_regex("\\.[a-z]+");
  std::smatch suffix;
  std::regex_search(file_path, suffix, dot_regex);
  std::string suffix_str = suffix[suffix.size() - 1];
  if (content_type.count(suffix_str) == 1) {
    add_head(HttpResponseHead::ContentType, content_type.find(suffix_str)->second);
  }
  add_head(HttpResponseHead::ContentLength, std::to_string(file::GetFileSize(file_path.c_str())));
}

void HttpResponse::set_client_socket_fd(int client_socket_fd) noexcept {
  client_socket_fd_ = client_socket_fd;
}
int HttpResponse::get_client_socket_fd() const noexcept {
  return client_socket_fd_;
}
