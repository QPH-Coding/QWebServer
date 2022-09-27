//
// Created by 钱沛桦 on 2022/9/26.
//

#include "task_queue.h"

template<typename T>
void TaskQueue<T>::Enqueue(const T &task) noexcept {
  std::unique_lock<std::mutex> lock(this->mutex_);
  this->tasks_.push(task);
}

template<typename T>
bool TaskQueue<T>::Dequeue(T &task) const noexcept {
  if (empty()) {
    return false;
  }
  std::unique_lock<std::mutex> lock(this->mutex_);
  task = std::move(this->tasks_.front());
  this->tasks_.pop();
  return true;
}

template<typename T>
int TaskQueue<T>::size() const noexcept {
  std::unique_lock<std::mutex> lock(this->mutex_);
  return this->tasks_.size();
}

template<typename T>
bool TaskQueue<T>::empty() const noexcept {
  std::unique_lock<std::mutex> lock(this->mutex_);
  return this->tasks_.empty();
}