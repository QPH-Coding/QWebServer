// Author: QPH-Coding
// Create: 2022/9/26
// File: server.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_SERVER_SERVER_H_
#define QWEBSERVER_SRC_SERVER_SERVER_H_
#include <string>
#include <unistd.h>
#include "../pool/thread_pool.hpp"
#include "../explanation/net.h"
#include "../http/http_connection.h"
#include "../explanation/epoll_listener.h"
#include "../time/time_wheel.h"
#include "../http/http_response.h"
#include "../log/async_log4q.h"

class QWebServer {
 public:
  QWebServer() noexcept;
  ~QWebServer() noexcept;
  void EventLoop();

 private:
  using client_fd = int;

  int listen_socket_fd_;
  ThreadPool<int> sub_reactor_read_; // responsible for reading from socket
  ThreadPool<HttpResponse> sub_reactor_write_; // responsible for writing to socket and send file
  ThreadPool<HttpConnection> service_; // responsible for deal with the http request
  TimeWheel time_wheel_;
  EpollListener epoll_listener_;
  static void SubReactorReadFunc(std::shared_ptr<int> &sp_client_fd, void *arg);
  static void SubReactorWriteFunc(std::shared_ptr<HttpResponse> &sp_http_response, void *arg);
  static void ServiceFunc(std::shared_ptr<HttpConnection> &sp_http_connection, void *arg);
  static const int MaxBufferSize;
};
#endif //QWEBSERVER_SRC_SERVER_SERVER_H_
