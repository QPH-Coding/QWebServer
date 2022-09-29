// Author: QPH-Coding
// Create: 2022/9/29
// File: thread_pool.hpp
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_
#define QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_

#include <memory>
#include <mutex>
#include <queue>

#include "../base/uncopyable.h"
#include "../explanation/thread.h"
#include "../explanation/semaphore.h"

template<typename T>
class ThreadPool : private Uncopyable {
 public:
  using deal_task_func = std::function<void(std::shared_ptr<T> &task)>;
  ThreadPool(int thread_num, int max_task_num, const deal_task_func& func) noexcept;
  ~ThreadPool() noexcept;

  void Start();

  void Enqueue(const std::shared_ptr<T> &task);

//  virtual void DealTask(const std::shared_ptr<T> &task) = 0;

 private:

  class WorkerThread : public Thread {
   public:
    void Start(ThreadPool<T> *thread_pool) noexcept;
    void Run() override;
   private:
    ThreadPool<T> *pthread_pool_;
  };

  int thread_num_;
  int max_task_num_;
  deal_task_func deal_task_func_;
  std::mutex task_mutex_;
  Semaphore task_semaphore_;
  std::vector<WorkerThread> thread_vector_;
  std::queue<std::shared_ptr<T>> task_queue_;
};

template<typename T>
void ThreadPool<T>::WorkerThread::Start(ThreadPool<T> *thread_pool) noexcept {
  pthread_pool_ = thread_pool;
  Thread::Start();
}

template<typename T>
void ThreadPool<T>::WorkerThread::Run() {
  while (true) {
    pthread_pool_->task_semaphore_.Wait();
    {
      std::lock_guard<std::mutex> lock(pthread_pool_->task_mutex_);
      if (pthread_pool_->task_queue_.empty()) {
        continue;
      }
    }
    std::shared_ptr<T> task;
    {
      std::lock_guard<std::mutex> lock(pthread_pool_->task_mutex_);
      task = pthread_pool_->task_queue_.front();
      if (!task) {
        continue;
      } else {
        pthread_pool_->task_queue_.pop();
      }
    }
    pthread_pool_->deal_task_func_(task);
  }
}

template<typename T>
ThreadPool<T>::ThreadPool(int thread_num, int max_task_num, const deal_task_func& func) noexcept
    :thread_num_(thread_num),
     max_task_num_(max_task_num),
     deal_task_func_(func) {
  assert(thread_num_ > 0);
  assert(max_task_num_ > 0);
  thread_vector_ = std::vector<WorkerThread>(thread_num_);
}

template<typename T>
ThreadPool<T>::~ThreadPool() noexcept {
  for (auto &thread : thread_vector_) {
    thread.Join();
  }
}

template<typename T>
void ThreadPool<T>::Start() {
  for (auto &thread : thread_vector_) {
    thread.Start(this);
    thread.Detach();
  }
}

template<typename T>
void ThreadPool<T>::Enqueue(const std::shared_ptr<T> &task) {
  std::lock_guard<std::mutex> lock(task_mutex_);
  if (task_queue_.size() >= max_task_num_) {
    // TODO log
    return;
  }
  task_queue_.push(task);
  task_semaphore_.Signal();
}

#endif //QWEBSERVER_SRC_POOL_THREAD_POOL_HPP_
