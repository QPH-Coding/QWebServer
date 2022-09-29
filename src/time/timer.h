// Author: QPH-Coding
// Create: 2022/9/29
// File: timer.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_TIME_TIMER_H_
#define QWEBSERVER_SRC_TIME_TIMER_H_

#include <sys/timerfd.h>
#include "../explanation/epoll_listener.h"
#include <functional>

class Timer {
 public:
  explicit Timer(int wait_second) noexcept;
  void Start() noexcept;
  void Stop() noexcept;
  void SetWaitTime(int wait_second) noexcept;
  virtual void OnTick() = 0;
 private:
  EpollListener epoll_listener_;
  int timer_fd_;
  int wait_second_;
  bool is_running_;
};
#endif //QWEBSERVER_SRC_TIME_TIMER_H_
