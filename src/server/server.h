// Author: QPH-Coding
// Create: 2022/9/26
// File: server.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_SERVER_SERVER_H_
#define QWEBSERVER_SRC_SERVER_SERVER_H_

#include <string>
#include <unistd.h>
#include <csignal>
#include <unordered_map>
#include <memory>
#include "../pool/thread_pool.hpp"
#include "../encapsulation/net.h"
#include "../http/http_connection.h"
#include "../encapsulation/epoll_listener.h"
#include "../time/time_wheel.h"
#include "../http/http_response.h"
#include "../http/http_service.h"
#include "../log/async_log4q.h"
#include "../pool/object_pool.hpp"
#include "../database/mysql_conn_raii.h"
#include "../database/mysql_deal.h"

// en:
// core code
// use multi-Reactor model deal with the event
// use TimeWheel manage connected socket
// use epoll listen read/write event
// zh:
// 核心代码
// 使用多Reactor模型处理事件
// 使用时间轮管理连接的socket
// 使用epoll监听读/写事件
class QWebServer {
 public:
  QWebServer() noexcept;
  ~QWebServer() noexcept;
  void Start();

 private:
  void EventLoop();
  using client_fd = int;
  enum class SubReactorTaskType {
    READ, WRITE, WAITING
  };
  // TODO can put the type in http connection
  struct ServerTask {
    SubReactorTaskType type_;
    HttpConnection http_connection_;
    explicit ServerTask(const Client &client) : http_connection_(client), type_(SubReactorTaskType::WAITING) {}
  };

  int listen_socket_fd_;
  ObjectPool<mysqlpp::Connection> mysql_conn_pool_;
  ThreadPool<ServerTask> sub_reactor_pool_;
  ThreadPool<ServerTask> service_pool_;
  TimeWheel time_wheel_;
  EpollListener epoll_listener_;

  static void SubReactorRead(std::shared_ptr<ServerTask> &sp_server_task, QWebServer *p_server);
  static void SubReactorWrite(std::shared_ptr<ServerTask> &sp_server_task, QWebServer *p_server);
  static void SubReactorFunc(std::shared_ptr<ServerTask> &sp_server_task, void *arg);
  static void ServiceFunc(std::shared_ptr<ServerTask> &sp_server_task, void *arg);

  std::unordered_map<int, std::shared_ptr<ServerTask>> fd_conn_map_;
};
#endif //QWEBSERVER_SRC_SERVER_SERVER_H_
