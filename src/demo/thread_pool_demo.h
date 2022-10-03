// Author: QPH-Coding
// Create: 2022/9/29
// File: thread_pool_demo.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
#define QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
#include "../pool/thread_pool.hpp"
#include "../log/async_log4q.h"

class ThreadPoolDemo {
 public:
  ThreadPoolDemo() noexcept;
  void Test();
 private:
  void ProduceTask();
  static void DealTask(std::shared_ptr<double> &task, void *arg);
  ThreadPool<double> thread_pool_;
};
#endif //QWEBSERVER_SRC_DEMO_THREAD_POOL_DEMO_H_
