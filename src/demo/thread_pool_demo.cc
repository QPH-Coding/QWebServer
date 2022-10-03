// Author: QPH-Coding
// Create: 2022/9/27
// File: thread_pool_demo.cc
// License: Apache 2.0

#include "thread_pool_demo.h"

#include <memory>

void ThreadPoolDemo::DealTask(std::shared_ptr<double> &task, void *arg) {
  std::string str = "deal task " + std::to_string(*task);
  AsyncLog4Q::Info(str);
}

void ThreadPoolDemo::ProduceTask() {
  for (int i = 0; i < 10; ++i) {
    thread_pool_.Enqueue(std::make_shared<double>(i));
    std::string str = "produce " + std::to_string(i);
    AsyncLog4Q::Info(str);
  }
}

void ThreadPoolDemo::Test() {
  thread_pool_.Start();
  for (int i = 0; i < 5; ++i) {
    std::thread producer(&ThreadPoolDemo::ProduceTask, this);
    producer.detach();
  }
}
ThreadPoolDemo::ThreadPoolDemo() noexcept
    : thread_pool_(5, 1000, ThreadPoolDemo::DealTask, this) {}
