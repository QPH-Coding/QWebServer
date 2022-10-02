#include <iostream>
#include "demo/epoll_demo.h"
//#include "demo/async_log_demo.h"
#include "demo/thread_pool_demo.h"

int main() {
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
//  EpollDemo epoll_demo;
//  epoll_demo.Test();

//  AsyncLog4Q::Init();
//  AsyncLogDemo();
  ThreadPoolDemo thread_pool_demo;
  thread_pool_demo.Test();
  while (true) {}
//  TimerTest test(2);
//  test.Start();
  return 0;
}
