// Author: QPH-Coding
// Create: 2022/9/29
// File: thread_pool.hpp
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_
#define QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_

#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>

#include "../base/uncopyable.h"
#include "../explanation/semaphore.h"
#include "../log/async_log4q.h"

template<typename T>
class ThreadPool : private Uncopyable {
 public:
  using deal_task_func = std::function<void(std::shared_ptr<T> &sp_task, void *arg)>;
  ThreadPool(int thread_num, int max_task_num, const deal_task_func &func, void *arg) noexcept;
  ~ThreadPool() noexcept;

  void Start();

  void Enqueue(const std::shared_ptr<T> &task);

 private:

  void WorkerThreadFunc();

  void *p_arg_;
  int thread_num_;
  int max_task_num_;
  deal_task_func deal_task_func_;
  std::mutex task_mutex_;
  Semaphore task_semaphore_;
  std::vector<std::thread> thread_vector_;
  std::queue<std::shared_ptr<T>> task_queue_;
};

template<typename T>
void ThreadPool<T>::WorkerThreadFunc() {
  while (true) {
    task_semaphore_.Wait();
    {
      std::lock_guard<std::mutex> lock(task_mutex_);
      if (task_queue_.empty()) {
        continue;
      }
    }
    std::shared_ptr<T> task;
    {
      std::lock_guard<std::mutex> lock(task_mutex_);
      task = task_queue_.front();
      if (!task) {
        continue;
      } else {
        task_queue_.pop();
      }
    }
    deal_task_func_(task, p_arg_);
  }
}

template<typename T>
ThreadPool<T>::ThreadPool(int thread_num, int max_task_num, const deal_task_func &func, void *arg) noexcept
    :thread_num_(thread_num),
     max_task_num_(max_task_num),
     deal_task_func_(func),
     p_arg_(arg) {
  assert(thread_num_ > 0);
  assert(max_task_num_ > 0);
  thread_vector_ = std::vector<std::thread>(thread_num_);
}

template<typename T>
ThreadPool<T>::~ThreadPool() noexcept {

}

template<typename T>
void ThreadPool<T>::Start() {
  for (auto &thread : thread_vector_) {
    thread = std::thread(&ThreadPool<T>::WorkerThreadFunc, this);
    thread.detach();
  }
}

template<typename T>
void ThreadPool<T>::Enqueue(const std::shared_ptr<T> &task) {
  std::lock_guard<std::mutex> lock(task_mutex_);
  if (task_queue_.size() >= max_task_num_) {
    AsyncLog4Q_Warn("The num of task exceeds the maximum, it will throw task.");
    return;
  }
  task_queue_.push(task);
  task_semaphore_.Signal();
}

#endif //QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_
