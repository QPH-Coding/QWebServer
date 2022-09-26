//
// Created by 钱沛桦 on 2022/9/26.
//
#include "semaphore.h"

Semaphore::Semaphore(int count) noexcept: count_(count) {}

void Semaphore::Signal() noexcept {
  std::unique_lock<std::mutex> lock(mutex_);
  ++count_;
  cv_.notify_one();
}

void Semaphore::Wait() noexcept {
  std::unique_lock<std::mutex> lock(mutex_);
  cv_.wait(lock, [=] { return count_ > 0; });
  --count_;
}