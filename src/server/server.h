// Author: QPH-Coding
// Create: 2022/9/26
// File: server.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_SERVER_SERVER_H_
#define QWEBSERVER_SRC_SERVER_SERVER_H_
#include <string>
#include "../pool/thread_pool.hpp"
#include "../explanation/net.h"
#include "../http/http_connection.h"
#include "../explanation/epoll_listener.h"
#include "../time/time_wheel.h"

class QWebServer {
 public:
//  QWebServer(int thread_num, int request_num)

  void EventLoop();

 private:
  ThreadPool<Client> sub_reactor_read_; // responsible for reading from socket
  ThreadPool<Response> sub_reactor_write_; // responsible for writing to socket and send file
  ThreadPool<HttpConnection> service_; // responsible for deal with the http request
  TimeWheel time_wheel_;
  EpollListener epoll_listener_;
//  static void SubReactorFunc(std::shared_ptr<Client> &sp_client);
//  static void ServiceFunc(std::shared_ptr<HttpConnection> &sp_http_connection);
};
#endif //QWEBSERVER_SRC_SERVER_SERVER_H_
