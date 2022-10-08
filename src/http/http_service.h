// Author: QPH-Coding
// Create: 2022/10/2
// File: http_service.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
#define QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
#include "http_request.h"
#include "http_response.h"
#include "../pool/object_pool.hpp"
#include <mysql++.h>
#include "../database/mysql_deal.h"

namespace http_service {

// TODO can redesign the structure
std::shared_ptr<HttpResponse> DealWithRequest(const HttpRequest &http_request,
                                              ObjectPool<mysqlpp::Connection> *mysql_conn_pool);

void UrlLogin(const HttpRequest &http_request,
              std::shared_ptr<HttpResponse> &sp_http_response,
              MySqlConnectionRaii &my_sql_connection_raii);

void UrlRegister(const HttpRequest &http_request,
                 std::shared_ptr<HttpResponse> &sp_http_response,
                 MySqlConnectionRaii &my_sql_connection_raii);

void UrlDelete(const HttpRequest &http_request,
               std::shared_ptr<HttpResponse> &sp_http_response,
               MySqlConnectionRaii &my_sql_connection_raii);

void UrlChange(const HttpRequest &http_request,
               std::shared_ptr<HttpResponse> &sp_http_response,
               MySqlConnectionRaii &my_sql_connection_raii);

void BasicResponse(const HttpRequest &http_request,
                   std::shared_ptr<HttpResponse> &sp_http_response);

void DefaultResponse(const HttpRequest &http_request,
                     std::shared_ptr<HttpResponse> &sp_http_response,
                     const std::string &url);
}

#endif //QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
