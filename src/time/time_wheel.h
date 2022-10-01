// Author: QPH-Coding
// Create: 2022/10/1
// File: time_wheel.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_TIME_TIME_WHEEL_H_
#define QWEBSERVER_SRC_TIME_TIME_WHEEL_H_

#include <unordered_map>
#include "timer.h"
#include "../explanation/thread.h"
#include "cycle_queue.hpp"

class TimeWheel : public Thread {
 public:
  TimeWheel() noexcept;
  // TODO maybe can optimize: set Thread::Start virtual?
  //  or use other method to set pointer
  void Start() noexcept;
  void add(int fd) noexcept;
  void Run() override;
 private:
  class CloseTimer : public Timer {
   public:
    CloseTimer() noexcept;
    void SetTimeWheel(TimeWheel *time_wheel) noexcept;
    void OnTick() override;
   private:
    TimeWheel *time_wheel_;
  };

  CloseTimer close_timer_;
  std::mutex mutex_;
  std::unordered_map<int, int> fd_count_map_;
  CycleQueue<std::vector<int>> cycle_queue_;
  std::vector<int> *p_pre_;
  std::vector<int> *p_curr_;
};

#endif //QWEBSERVER_SRC_TIME_TIME_WHEEL_H_
