// Author: QPH-Coding
// Create: 2022/10/2
// File: http_service.cc
// License: Apache 2.0

#include "http_service.h"

HttpResponse HttpService::DealWithRequest(const HttpRequest &http_request) {
  if (!http_request.is_effective()) {
    HttpResponse http_response;
    http_response.set_protocol_version(http_request.get_protocol());
    http_response.set_status(HttpResponseStatus::BadRequest);
    return http_response;
  }

  HttpRequest::Method method = http_request.get_method();
  std::string url = http_request.get_url();
  if (method == HttpRequest::Method::GET && url == "/") {

  }
}