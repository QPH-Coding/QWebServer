// Author: QPH-Coding
// Create: 2022/10/1
// File: cycle_queue.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_TIME_CYCLE_QUEUE_HPP_
#define QWEBSERVER_SRC_TIME_CYCLE_QUEUE_HPP_

#include <vector>

template<typename T>
class CycleQueue {
 public:
  CycleQueue() noexcept;
  explicit CycleQueue(int initial_size) noexcept;
  void add() noexcept;
  void add(const T &item) noexcept;
  int size() const noexcept;
  T *next() noexcept;

 private:
  std::vector<T> queue_;
  int index_;
};

template<typename T>
CycleQueue<T>::CycleQueue() noexcept
    :queue_(std::vector<T>()),
     index_(0) {}

template<typename T>
CycleQueue<T>::CycleQueue(int initial_size) noexcept
    :queue_(std::vector<T>(initial_size)),
     index_(0) {}

template<typename T>
void CycleQueue<T>::add() noexcept {
  queue_.push_back(std::vector<T>());
}

template<typename T>
void CycleQueue<T>::add(const T &item) noexcept {
  queue_.push_back(item);
}

template<typename T>
int CycleQueue<T>::size() const noexcept {
  return queue_.size();
}

template<typename T>
T *CycleQueue<T>::next() noexcept {
  ++index_;
  if (index_ >= queue_.size()) {
    index_ = 0;
  }
  return &queue_[index_];
}

#endif //QWEBSERVER_SRC_TIME_CYCLE_QUEUE_HPP_
