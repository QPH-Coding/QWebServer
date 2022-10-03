#include <iostream>
#include "demo/epoll_demo.h"
//#include "demo/async_log_demo.h"
#include "demo/thread_pool_demo.h"
#include "server/server.h"

int main() {
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
//  EpollDemo epoll_demo;
//  epoll_demo.Test();

//  AsyncLog4Q::Init();
//  AsyncLogDemo();
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
//  while (true) {}
//  TimerTest test(2);
//  test.Start();
  QWebServer q_web_server;
  q_web_server.EventLoop();
  return 0;
}
