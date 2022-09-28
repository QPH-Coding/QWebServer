//
// Created by 钱沛桦 on 2022/9/26.
//
#pragma once
#ifndef QWEBSERVER_SRC_POOL_TASKQUEUE_H_
#define QWEBSERVER_SRC_POOL_TASKQUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include "../base/uncopyable.h"

template<typename T>
class TaskQueue : private Uncopyable {
 public:
  explicit TaskQueue(size_t max_task_num = 1000) noexcept;
  ~TaskQueue() noexcept;

  void enqueue(const std::shared_ptr<T> &task) noexcept;
  std::shared_ptr<T> dequeue() noexcept;
  int size() const noexcept;
  size_t capacity() const noexcept;
  bool empty() const noexcept;
  bool full() const noexcept;
  bool closed() const noexcept;

 private:
  size_t max_task_num_;
  bool is_closed;
  mutable std::mutex mutex_;
  std::queue<std::shared_ptr<T>> tasks_;
};

template<typename T>
TaskQueue<T>::TaskQueue(size_t max_task_num) noexcept
    :max_task_num_(max_task_num) {
  assert(max_task_num_ > 0);
  is_closed = false;
}
template<typename T>
TaskQueue<T>::~TaskQueue() noexcept {
  std::lock_guard<std::mutex> lock(mutex_);
  is_closed = true;
}

template<typename T>
bool TaskQueue<T>::closed() const noexcept {
  std::lock_guard<std::mutex> lock(mutex_);
  return is_closed;
}

//template<typename T>
//void TaskQueue<T>::enqueue(T *task) noexcept {
//  std::unique_lock<std::mutex> lock(mutex_);
//  tasks_.push(task);
//}

template<typename T>
void TaskQueue<T>::enqueue(const std::shared_ptr<T> &task) noexcept {
  std::lock_guard<std::mutex> lock(mutex_);
  tasks_.push(task);
}

template<typename T>
std::shared_ptr<T> TaskQueue<T>::dequeue() noexcept {
  std::unique_lock<std::mutex> lock(mutex_);
  if (tasks_.empty()) {
    return std::shared_ptr<T>(nullptr);
  }
  std::shared_ptr<T> res = std::move(tasks_.front());
  tasks_.pop();
  return std::move(res);
}

template<typename T>
int TaskQueue<T>::size() const noexcept {
  std::lock_guard<std::mutex> lock(this->mutex_);
  return this->tasks_.size();
}

template<typename T>
bool TaskQueue<T>::empty() const noexcept {
  std::lock_guard<std::mutex> lock(this->mutex_);
  return this->tasks_.empty();
}

template<typename T>
size_t TaskQueue<T>::capacity() const noexcept {
  return max_task_num_;
}

template<typename T>
bool TaskQueue<T>::full() const noexcept {
  return tasks_.size() == max_task_num_;
}
#endif //QWEBSERVER_SRC_POOL_TASKQUEUE_H_
