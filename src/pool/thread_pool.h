// Author: QPH-Coding
// Create: 2022/9/26
// File: thread_pool.h
// License: Apache 2.0

#pragma once
#ifndef QWEBSERVER_SRC_POOL_THREAD_POOL_H_
#define QWEBSERVER_SRC_POOL_THREAD_POOL_H_
#include <functional>
#include <memory>
#include <condition_variable>
#include "task_queue.hpp"
#include "../explanation/thread.h"
#include "../explanation/semaphore.h"
#include "../base/uncopyable.h"

// TODO use HTTP Connection instead of double
class ThreadPool : private Uncopyable {
 public:
  ~ThreadPool() noexcept = default;

  static ThreadPool &get_instance() noexcept;
  void Start(int thread_num);
  void EnqueueTask(const std::shared_ptr<double> &task) const noexcept;
 private:
  ThreadPool() noexcept = default;

  class WorkThread : public Thread {
   public:
    void Run() override;
  };

  static ThreadPool instance_;
  static Semaphore task_semaphore_;
  static TaskQueue<double> task_queue_;
  std::vector<WorkThread> thread_vector_;
};

#endif //QWEBSERVER_SRC_POOL_THREAD_POOL_H_
