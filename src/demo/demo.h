// Author: QPH-Coding
// Create: 2022/9/26
// File: demo.h
// License: Apache 2.0

#include "../explanation/epoll_listener.h"
#include "../pool/thread_pool.h"
#include <unistd.h>

class EpollDemo {
 public:
  void Test();
};

class ThreadPoolDemo {
 public:
  void Test();
 private:
  class ProducerThread : public Thread {
   public:
    void Run() override;

  };
};