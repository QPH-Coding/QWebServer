// Author: QPH-Coding
// Create: 2022/10/2
// File: http_request.cc
// License: Apache 2.0

#include "http_request.h"

const std::regex HttpRequest::split_line_regex_ = std::regex("\r\n");

const std::regex HttpRequest::split_head_body_regex_ = std::regex("\r\n\r\n");

const std::regex HttpRequest::space_regex_ = std::regex(" ");

const std::regex HttpRequest::colon_regex_ = std::regex(": ");

HttpRequest::HttpRequest(const std::string &raw_request_) noexcept {
  Analyze(raw_request_);
}

HttpRequest::Method HttpRequest::get_method() const noexcept {
  return method_;
}

std::string HttpRequest::get_url() const noexcept {
  return url_;
}

std::string HttpRequest::get_protocol() const noexcept {
  return protocol_version_;
}

std::string HttpRequest::get_request_body() const noexcept {
  return request_body_;
}

std::string HttpRequest::get_head(const http_request_head &head_key) const noexcept {
  if (request_head_.count(head_key) == 1) {
    return request_head_.find(head_key)->second;
  }
  return "";
}

void HttpRequest::Analyze(const std::string &raw_request_) noexcept {
  // en: split {request line, request head} and {request body}
  // zh: 分割{请求行，请求头}和{请求实体}
  std::sregex_token_iterator
      request_line_heads_it{raw_request_.begin(), raw_request_.end(), split_head_body_regex_, -1},
      request_line_heads_end_it;
  // en:
  // judge the format of the HTTP request is correct
  // I will check the format at every place after operating the iterator
  if (!JudgeFormat(request_line_heads_it, request_line_heads_end_it)) {
    is_effective_ = false;
    return;
  }
  std::string request_line_heads = request_line_heads_it->str();
  ++request_line_heads_it;
  // en: if iterator == end, the request body is null
  // zh: 如果 iterator == end，请求实体为空
  if (request_line_heads_it == request_line_heads_end_it) {
    request_body_ = "";
  } else {
    request_body_ = request_line_heads_it->str();
  }

  // en: split {request line} and {request heads}
  // zh: 分割{请求行}和{请求头}
  std::sregex_token_iterator
      first{request_line_heads.begin(), request_line_heads.end(), split_line_regex_, -1},
      last;
  if (!JudgeFormat(first, last)) {
    is_effective_ = false;
    return;
  }
  std::string request_line = first->str();
  ++first;
  std::vector<std::string> request_heads{first, last};

  // en: analyze request line
  // zh: 分析请求行
  std::sregex_token_iterator
      request_line_it{request_line.begin(), request_line.end(), space_regex_, -1},
      request_line_end_it;
  if (!JudgeFormat(request_line_it, request_line_end_it)) {
    is_effective_ = false;
    return;
  }
  std::string method = request_line_it->str();
  if (method == "GET") {
    method_ = Method::GET;
  } else if (method == "POST") {
    method_ = Method::POST;
  } else if (method == "DELETE") {
    method_ = Method::DELETE;
  } else {
    is_effective_ = false;
    return;
  }
  ++request_line_it;
  if (!JudgeFormat(request_line_it, request_line_end_it)) {
    is_effective_ = false;
    return;
  }
  url_ = request_line_it->str();
  ++request_line_it;
  if (!JudgeFormat(request_line_it, request_line_end_it)) {
    is_effective_ = false;
    return;
  }
  protocol_version_ = request_line_it->str();

  // en: analyze request head
  // zh: 分析请求头
  for (auto &head_line : request_heads) {
    std::sregex_token_iterator
        head_it{head_line.begin(), head_line.end(), colon_regex_, -1},
        head_end_it;
    if (!JudgeFormat(head_it, head_end_it)) {
      is_effective_ = false;
      return;
    }
    std::string head_key = head_it->str();
    ++head_it;
    if (!JudgeFormat(head_it, head_end_it)) {
      is_effective_ = false;
      return;
    }
    std::string head_value = head_it->str();
    request_head_[head_key] = head_value;
  }
  is_effective_ = true;
}

bool HttpRequest::JudgeFormat(const std::sregex_token_iterator &lhs,
                              const std::sregex_token_iterator &rhs) noexcept {
  return lhs != rhs;
}

bool HttpRequest::is_effective() const noexcept {
  return is_effective_;
}

