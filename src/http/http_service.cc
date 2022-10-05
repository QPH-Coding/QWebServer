// Author: QPH-Coding
// Create: 2022/10/2
// File: http_service.cc
// License: Apache 2.0

#include "http_service.h"

std::shared_ptr<HttpResponse> HttpService::DealWithRequest(const HttpRequest &http_request,
                                                           ObjectPool<mysqlpp::Connection> *mysql_conn_pool) {
  std::shared_ptr<HttpResponse> http_response(new HttpResponse);
  http_response->set_protocol_version();
  if (!http_request.is_effective()) {
    http_response->set_status(HttpResponseStatus::BadRequest);
    return http_response;
  }

  HttpRequest::Method method = http_request.get_method();
  std::string url = http_request.get_url();
  if (url == "/") {
    http_response->set_status(HttpResponseStatus::OK);
    http_response->add_file("/server/root/index.html");
    return http_response;
  } else if (url == "/login") {
    http_response->set_status(HttpResponseStatus::OK);
    http_response->add_head(HttpResponseHead::ContentType, "application/json");


    std::string resp_body = "{\"status\": true}";
    http_response->add_head(HttpResponseHead::ContentLength, std::to_string(resp_body.length() * sizeof(char)));
    http_response->set_response_body(resp_body);
    return http_response;
  }

  http_response->set_status(HttpResponseStatus::NotFound);
  return http_response;
}