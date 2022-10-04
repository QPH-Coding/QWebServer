// Author: QPH-Coding
// Create: 2022/10/1
// File: time_wheel.cc
// License: Apache 2.0

#include "time_wheel.h"
TimeWheel::TimeWheel() noexcept
    : mutex_(std::mutex()),
      close_timer_(CloseTimer()),
      fd_count_map_(std::unordered_map<int, int>()),
      cycle_queue_(CycleQueue<std::vector<int>>(8)) {
  p_pre_ = cycle_queue_.next();
  p_curr_ = cycle_queue_.next();
}

void TimeWheel::Start() noexcept {
  close_timer_.SetTimeWheel(this);
  std::thread time_wheel_thread([&] { close_timer_.Start(); });
  time_wheel_thread.detach();
}

void TimeWheel::add(int fd) noexcept {
  std::lock_guard<std::mutex> lock(mutex_);
  p_pre_->push_back(fd);
  ++fd_count_map_[fd];
  AsyncLog4Q_Info("TimeWheel add fd: " + std::to_string(fd));
}

void TimeWheel::Close() {
  std::lock_guard<std::mutex> lock(mutex_);
  for (int i = 0; i < 8; ++i) {
    for (auto &fd : *p_curr_) {
      close(fd);
    }
    p_curr_->clear();
    p_pre_ = p_curr_;
    p_curr_ = cycle_queue_.next();
  }
}

TimeWheel::CloseTimer::CloseTimer() noexcept: Timer(1) {}

void TimeWheel::CloseTimer::SetTimeWheel(TimeWheel *time_wheel) noexcept {
  time_wheel_ = time_wheel;
}

void TimeWheel::CloseTimer::OnTick() {
  // en: check the unordered map, if the fd's value is 0, close it
  // zh: 检查映射表中fd的值是否为0，若为0，则关闭这个fd
  for (auto &fd : *(time_wheel_->p_curr_)) {
    --time_wheel_->fd_count_map_[fd];
    if (time_wheel_->fd_count_map_[fd] == 0) {
      close(fd);
      AsyncLog4Q_Info("TimeWheel close fd: " + std::to_string(fd));
    }
  }
  // en: while operating the pointer, lock the mutex
  // zh: 在对指针进行操作的时候上锁
  std::lock_guard<std::mutex> lock(time_wheel_->mutex_);
  time_wheel_->p_curr_->clear();
  time_wheel_->p_pre_ = time_wheel_->p_curr_;
  time_wheel_->p_curr_ = time_wheel_->cycle_queue_.next();
}
