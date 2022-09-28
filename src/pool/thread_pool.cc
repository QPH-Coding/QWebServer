//
// Created by 钱沛桦 on 2022/9/26.
//
#include "thread_pool.h"

ThreadPool ThreadPool::instance_ = ThreadPool();

Semaphore ThreadPool::task_semaphore_ = Semaphore();

TaskQueue<double> ThreadPool::task_queue_ = TaskQueue<double>();

ThreadPool &ThreadPool::get_instance() noexcept {
  return instance_;
}

void ThreadPool::Start(const int thread_num) {
  // TODO maybe can be optimize
  // 1. config startup sequence maybe can make it get value during compilation
  // 2. use other way to construct shared_ptr
  thread_vector_ = std::vector<WorkThread>(thread_num);
  for (auto &thread : thread_vector_) {
    thread.Start();
  }
  for (auto &thread : thread_vector_) {
    thread.Detach();
  }
}

void ThreadPool::EnqueueTask(const std::shared_ptr<double> &task) const noexcept {
  task_queue_.enqueue(task);
  task_semaphore_.Signal();
}

void ThreadPool::WorkThread::Run() {
  while (true) {
    task_semaphore_.Wait();
    if (task_queue_.empty()) {
      continue;
    }
    std::shared_ptr<double> task = task_queue_.dequeue();
    if (!task) {
      continue;
    }
    // TODO deal with task
    std::cout << "thread " << gettid() << " : " << *task << std::endl;
  }
}
