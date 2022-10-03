// Author: QPH-Coding
// Create: 2022/10/2
// File: http_service.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
#define QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
#include "http_request.h"
#include "http_response.h"

namespace HttpService {

HttpResponse DealWithRequest(const HttpRequest &http_request);


}

#endif //QWEBSERVER_SRC_HTTP_HTTP_SERVICE_H_
