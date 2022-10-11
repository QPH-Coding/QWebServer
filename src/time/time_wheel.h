// Author: QPH-Coding
// Create: 2022/10/1
// File: time_wheel.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_TIME_TIME_WHEEL_H_
#define QWEBSERVER_SRC_TIME_TIME_WHEEL_H_

#include <unordered_map>
#include <thread>
#include "cycle_queue.hpp"
#include "timer.h"
#include "../log/async_log4q.h"

// en:
// manage connected socket
// use cycle queue store the connected socket
// use std::unordered_map count connected socket num
// zh:
// 管理连接的socket
// 使用循环队列存储连接的socket
// 使用std::unordered_map统计连接的socket数量
class TimeWheel {
 public:
  TimeWheel() noexcept;
  void Start() noexcept;
  void add(int fd) noexcept;
  void Close();
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
