#include <iostream>
#include "demo/demo.h"

int main() {
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
  EpollDemo epoll_demo;
  epoll_demo.Test();
  return 0;
}
