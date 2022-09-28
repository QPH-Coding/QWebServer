//
// Created by 钱沛桦 on 2022/9/26.
//
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