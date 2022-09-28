// Author: QPH-Coding
// Create: 2022/9/27
// File: thread_pool_demo.cc
// License: Apache 2.0

#include "demo.h"

#include <memory>

void test_func() {
  std::cout << gettid() << std::endl;
}

void ThreadPoolDemo::Test() {
  ThreadPool::get_instance().Start(5);

  ProducerThread producer_thread_0;
  ProducerThread producer_thread_1;
  ProducerThread producer_thread_2;

  producer_thread_0.Start();
  producer_thread_1.Start();
  producer_thread_2.Start();

  producer_thread_0.Join();
  producer_thread_1.Join();
  producer_thread_2.Join();
}

void ThreadPoolDemo::ProducerThread::Run() {
  for (int i = 0; i < 5; ++i) {
    sleep(1);
    std::cout << "producer " << gettid() << " will produce: " << i << std::endl;
    std::shared_ptr<double> task = std::make_shared<double>(i);
    ThreadPool::get_instance().EnqueueTask(task);
  }
}
