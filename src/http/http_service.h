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

namespace HttpService {

// TODO can redesign the structure
std::shared_ptr<HttpResponse> DealWithRequest(const HttpRequest &http_request,
                                              ObjectPool<mysqlpp::Connection> *mysql_conn_pool);

}

#endif //QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
