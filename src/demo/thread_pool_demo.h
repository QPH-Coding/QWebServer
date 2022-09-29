// Author: QPH-Coding
// Create: 2022/9/29
// File: thread_pool_demo.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
#define QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
#include "../pool/thread_pool.hpp"

void deal_task(std::shared_ptr<double> &task);

class ThreadPoolDemo {
 public:
  void Test();
 private:
  class ProducerThread : public Thread {
   public:
    explicit ProducerThread(ThreadPool<double> *thread_pool);
    void Run() override;

   private:
    ThreadPool<double> *thread_pool_;
  };
};
#endif //QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
