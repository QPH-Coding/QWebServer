//
// Created by 钱沛桦 on 2022/9/26.
//

#include "task_queue.h"

template<typename T>
void TaskQueue<T>::PushTask(const T &task) noexcept {
  std::unique_lock<std::mutex> lock(this->mutex_);
  this->tasks_.push(task);
}

template<typename T>
T TaskQueue<T>::PopTask() const noexcept {
  std::unique_lock<std::mutex> lock(this->mutex_);
  T task = this->tasks_.front();
  this->tasks_.pop();
  return task;
}

template<typename T>
int TaskQueue<T>::get_tasks_num() const noexcept {
  return this->tasks_.size();
}