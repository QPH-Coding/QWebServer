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

void HttpResponse::set_response_body(const char *response_body,
                                     long whole_file_size,
                                     long start_index,
                                     long end_index) noexcept {
  long index = 0;
  if (end_index == -1) {
    response_body_.resize(whole_file_size - start_index);
    for (long i = start_index; i < whole_file_size; ++i) {
      response_body_[index++] = response_body[i];
    }
  } else {
    response_body_.resize(end_index - start_index);
    for (long i = start_index; i < end_index; ++i) {
      response_body_[index++] = response_body[i];
    }
  }
}
std::vector<char> HttpResponse::get_response_header() const noexcept {
  std::string http_response_string;
  http_response_string += protocol_version_ + " "
      + std::to_string(status_.first) + " "
      + status_.second + "\r\n";
  for (auto &head : response_head_) {
    http_response_string += head.first + ": " + head.second + "\r\n";
  }
  http_response_string += "\r\n";
  std::vector<char> response_header(http_response_string.size());
  for (int i = 0; i < http_response_string.size(); ++i) {
    response_header[i] = http_response_string[i];
  }
  return {response_header.begin() + header_index_, response_header.end()};
}
bool HttpResponse::add_file(const std::string &file_path, long start_index, long end_index) noexcept {
  int file_fd = open(file_path.c_str(), O_RDONLY);
  if (file_fd < 0) {
    set_status(HttpResponseStatus::NotFound);
    return false;
  }

  std::string range;
  long file_size, whole_file_size;
  whole_file_size = file::GetFileSize(file_path.c_str());
  if (end_index == -1 && start_index == 0) {
    file_size = whole_file_size;
  } else if (start_index != 0 && end_index == -1) {
    file_size = whole_file_size - start_index;
    range += std::to_string(start_index) + "-" + std::to_string(whole_file_size);
  } else {
    file_size = end_index - start_index;
    range += std::to_string(start_index) + "-" + std::to_string(end_index);
  }
  int *mm_file = (int *) mmap(nullptr, (size_t) whole_file_size, PROT_READ, MAP_PRIVATE, file_fd, 0);
  if (*mm_file == -1) {
    AsyncLog4Q_Warn("mmap " + file_path + " failed.");
  }
  set_response_body((char *) mm_file, whole_file_size, start_index, end_index);
  close(file_fd);
  int ret = munmap(mm_file, file_size);
  if (ret == -1) {
    AsyncLog4Q_Warn("mun-map " + file_path + " failed.");
  }

  // en: add content-type header by suffix automatically
  // zh: 自动添加content-type头根据文件后缀
  std::regex dot_regex("\\.[a-z,A-Z,0-9]+");
  std::smatch suffix;
  std::regex_search(file_path, suffix, dot_regex);
  std::string suffix_str = suffix[suffix.size() - 1];
  if (content_type.count(suffix_str) == 1) {
    add_head(HttpResponseHead::ContentType, content_type.find(suffix_str)->second);
  }
  add_head(HttpResponseHead::ContentLength, std::to_string(file_size));
  if (!range.empty()) {
    add_head(HttpResponseHead::ContentRange, range);
  }
  return true;
}

std::vector<char> HttpResponse::get_response_body() {
  return {response_body_.begin() + body_index_, response_body_.end()};
}
void HttpResponse::append_body_index(long body_index) noexcept {
  body_index_ += body_index;
}
void HttpResponse::set_have_write_head() noexcept {
  have_write_head_ = true;
}
bool HttpResponse::is_have_write_head() const noexcept {
  return have_write_head_;
}
void HttpResponse::append_header_index(long header_index) noexcept {
  header_index_ += header_index;
}
const HttpResponse::http_response_status &HttpResponse::get_response_status() noexcept {
  return status_;
}
