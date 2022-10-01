// Author: QPH-Coding
// Create: 2022/9/29
// File: http_connection.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_
#define QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_

#include "../explanation/net.h"

class HttpConnection {

 public:
  HttpConnection(const Client &client, const std::string raw_string);

};

#endif //QWEBSERVER_SRC_HTTP_HTTP_CONNECTION_H_