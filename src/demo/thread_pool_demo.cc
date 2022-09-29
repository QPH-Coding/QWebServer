// Author: QPH-Coding
// Create: 2022/9/27
// File: thread_pool_demo.cc
// License: Apache 2.0

#include "thread_pool_demo.h"

#include <memory>

void deal_task(std::shared_ptr<double> &task) {
  std::cout << gettid() << ": " << *task << std::endl;
}

void ThreadPoolDemo::Test() {

  ThreadPool<double> thread_pool(5, 100, deal_task);
  thread_pool.Start();

  ProducerThread producer_thread_0(&thread_pool);
  ProducerThread producer_thread_1(&thread_pool);
  ProducerThread producer_thread_2(&thread_pool);

  producer_thread_0.Start();
  producer_thread_1.Start();
  producer_thread_2.Start();

  producer_thread_0.Join();
  producer_thread_1.Join();
  producer_thread_2.Join();
}

ThreadPoolDemo::ProducerThread::ProducerThread(ThreadPool<double> *thread_pool)
    : thread_pool_(thread_pool) {}

void ThreadPoolDemo::ProducerThread::Run() {
  for (int i = 0; i < 5; ++i) {
    sleep(1);
    std::cout << "producer " << gettid() << " will produce: " << i << std::endl;
    std::shared_ptr<double> task = std::make_shared<double>(i);
    thread_pool_->Enqueue(task);
  }
}
