// Author: QPH-Coding
// Create: 2022/10/2
// File: http_service.cc
// License: Apache 2.0

#include "http_service.h"

std::shared_ptr<HttpResponse> http_service::DealWithRequest(const HttpRequest &http_request,
                                                            ObjectPool<mysqlpp::Connection> *mysql_conn_pool) {
  std::shared_ptr<HttpResponse> sp_http_response(new HttpResponse);
  http_service::BasicResponse(http_request, sp_http_response);

  std::string url = http_request.get_url();
  if (url.empty()) {
    sp_http_response->set_status(HttpResponseStatus::BadRequest);
    sp_http_response->add_file(Config::Root() + "/400.html");
  } else if (url == "/") {
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_file(Config::Root() + "/index.html");
  } else if (url == "/login") {
    MySqlConnectionRaii my_sql_connection_raii(mysql_conn_pool);
    http_service::UrlLogin(http_request, sp_http_response, my_sql_connection_raii);
  } else if (url == "/register") {
    MySqlConnectionRaii my_sql_connection_raii(mysql_conn_pool);
    http_service::UrlRegister(http_request, sp_http_response, my_sql_connection_raii);
  } else if (url == "/delete") {
    MySqlConnectionRaii my_sql_connection_raii(mysql_conn_pool);
    http_service::UrlDelete(http_request, sp_http_response, my_sql_connection_raii);
  } else if (url == "/change") {
    MySqlConnectionRaii my_sql_connection_raii(mysql_conn_pool);
    http_service::UrlChange(http_request, sp_http_response, my_sql_connection_raii);
  } else {
    http_service::DefaultResponse(http_request, sp_http_response, url);
  }
  return sp_http_response;
}

void http_service::UrlLogin(const HttpRequest &http_request,
                            std::shared_ptr<HttpResponse> &sp_http_response,
                            MySqlConnectionRaii &my_sql_connection_raii) {
  HttpRequest::Method method = http_request.get_method();
  if (method == HttpRequest::Method::GET) {
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_file(Config::Root() + "/index.html");
  } else if (method == HttpRequest::Method::POST) {
    std::string request_body = http_request.get_request_body();
    Json::Value request_json;
    Json::Reader reader;
    reader.parse(request_body, request_json);
    std::string response_body;
    if (mysql_deal::CheckUserPassword(request_json["user"].asString(),
                                      request_json["password"].asString(),
                                      my_sql_connection_raii)) {
      response_body = "{\"status\": true}";
    } else {
      response_body = "{\"status\": false}";
    }
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_head(HttpResponseHead::ContentType, "application/json");
    sp_http_response->add_head(HttpResponseHead::ContentLength, std::to_string(response_body.length() * sizeof(char)));
    sp_http_response->set_response_body(response_body.c_str(), response_body.length());
  } else {
    sp_http_response->set_status(HttpResponseStatus::MethodNotAllowed);
    sp_http_response->add_file(Config::Root() + "/405.html");
  }
}

void http_service::UrlRegister(const HttpRequest &http_request,
                               std::shared_ptr<HttpResponse> &sp_http_response,
                               MySqlConnectionRaii &my_sql_connection_raii) {
  HttpRequest::Method method = http_request.get_method();
  if (method == HttpRequest::Method::GET) {
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_file(Config::Root() + "/register.html");
  } else if (method == HttpRequest::Method::POST) {
    std::string request_body = http_request.get_request_body();
    Json::Value request_json;
    Json::Reader reader;
    reader.parse(request_body, request_json);
    std::string response_body;
    if (mysql_deal::AddUser(request_json["user"].asString(),
                            request_json["password"].asString(),
                            my_sql_connection_raii)) {
      response_body = "{\"status\": true}";
    } else {
      response_body = "{\"status\": false}";
    }
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_head(HttpResponseHead::ContentType, "application/json");
    sp_http_response->add_head(HttpResponseHead::ContentLength, std::to_string(response_body.length() * sizeof(char)));
    sp_http_response->set_response_body(response_body.c_str(), response_body.length());
  } else {
    sp_http_response->set_status(HttpResponseStatus::MethodNotAllowed);
    sp_http_response->add_file(Config::Root() + "/405.html");
  }
}

void http_service::BasicResponse(const HttpRequest &http_request, std::shared_ptr<HttpResponse> &sp_http_response) {
  sp_http_response->set_protocol_version();
  if (!http_request.is_effective()) {
    sp_http_response->set_status(HttpResponseStatus::BadRequest);
  }
  if (http_request.get_head(HttpRequestHead::Connection) == "keep-alive") {
    sp_http_response->add_head(HttpResponseHead::Connection, "keep-alive");
    sp_http_response->add_head(HttpResponseHead::KeepAlive, "timeout=8, max=100");
  }
}

void http_service::DefaultResponse(const HttpRequest &http_request,
                                   std::shared_ptr<HttpResponse> &sp_http_response,
                                   const std::string &url) {
  // en:
  // analyze the 'Range' in request
  // use regex change: bytes=123-1245 -> 123-1245 -> start_index = 123, end_index = 1245
  // zh:
  // 分析请求中的Range字段
  // 使用正则表达式的变化: bytes=123-1245 -> 123-1245 -> start_index = 123, end_index = 1245
  std::string request_head_range = http_request.get_head(HttpRequestHead::Range);
  long start_index = 0, end_index = -1;
  if (!request_head_range.empty()) {
    std::regex get_range_regex("[0-9]+-[0-9]*");
    std::smatch range_match;
    std::regex_search(request_head_range, range_match, get_range_regex);

    if (range_match.size() != 1) {
      AsyncLog4Q_Warn("Match 'Range' " + request_head_range + " failed.");
      sp_http_response->set_status(HttpResponseStatus::InternalServerError);
      sp_http_response->add_file(Config::Root() + "/500.html");
      return;
    } else {
      std::string range = range_match[0];
      std::regex split_regex("-");
      std::sregex_token_iterator
          range_it{range.begin(), range.end(), split_regex, -1},
          range_end_it;
      if (range_it == range_end_it) {
        AsyncLog4Q_Warn("Split 'Range' " + range + " failed.");
        sp_http_response->set_status(HttpResponseStatus::InternalServerError);
        sp_http_response->add_file(Config::Root() + "/500.html");
        return;
      }
      start_index = std::stol(range_it->str());
      ++range_it;
      if (range_it != range_end_it) {
        end_index = std::stol(range_it->str());
      }
      if (sp_http_response->add_file(Config::Root() + url, start_index, end_index)) {
        if (start_index == 0) {
          sp_http_response->set_status(HttpResponseStatus::OK);
        } else {
          sp_http_response->set_status(HttpResponseStatus::PartialContent);
        }
      } else {
        sp_http_response->add_file(Config::Root() + "/404.html");
      }
    }
  } else {
    if (sp_http_response->add_file(Config::Root() + url)) {
      sp_http_response->set_status(HttpResponseStatus::OK);
    } else {
      sp_http_response->add_file(Config::Root() + "/404.html");
    }
  }
}

void http_service::UrlDelete(const HttpRequest &http_request,
                             std::shared_ptr<HttpResponse> &sp_http_response,
                             MySqlConnectionRaii &my_sql_connection_raii) {
  HttpRequest::Method method = http_request.get_method();
  if (method != HttpRequest::Method::DELETE) {
    sp_http_response->set_status(HttpResponseStatus::MethodNotAllowed);
    sp_http_response->add_file(Config::Root() + "/405.html");
  } else {
    std::string request_body = http_request.get_request_body();
    Json::Value request_json;
    Json::Reader reader;
    reader.parse(request_body, request_json);
    std::string user = request_json["user"].asString();
    std::string password = request_json["password"].asString();
    std::string response_body;
    if (mysql_deal::DeleteUser(user, password, my_sql_connection_raii)) {
      response_body = "{\"status\": true}";
    } else {
      response_body = "{\"status\": false}";
    }
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_head(HttpResponseHead::ContentType, "application/json");
    sp_http_response->add_head(HttpResponseHead::ContentLength, std::to_string(response_body.length() * sizeof(char)));
    sp_http_response->set_response_body(response_body.c_str(), response_body.length());
  }
}

void http_service::UrlChange(const HttpRequest &http_request,
                             std::shared_ptr<HttpResponse> &sp_http_response,
                             MySqlConnectionRaii &my_sql_connection_raii) {
  HttpRequest::Method method = http_request.get_method();
  if (method != HttpRequest::Method::POST) {
    sp_http_response->set_status(HttpResponseStatus::MethodNotAllowed);
    sp_http_response->add_file(Config::Root() + "/405.html");
  } else {
    std::string request_body = http_request.get_request_body();
    Json::Value request_json;
    Json::Reader reader;
    reader.parse(request_body, request_json);
    std::string user = request_json["user"].asString();
    std::string old_password = request_json["old"].asString();
    std::string new_password = request_json["new"].asString();
    std::string response_body;
    if (mysql_deal::ChangePassword(user, old_password, new_password, my_sql_connection_raii)) {
      response_body = "{\"status\": true}";
    } else {
      response_body = "{\"status\": false}";
    }
    sp_http_response->set_status(HttpResponseStatus::OK);
    sp_http_response->add_head(HttpResponseHead::ContentType, "application/json");
    sp_http_response->add_head(HttpResponseHead::ContentLength, std::to_string(response_body.length() * sizeof(char)));
    sp_http_response->set_response_body(response_body.c_str(), response_body.length());
  }
}