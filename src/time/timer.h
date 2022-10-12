// Author: QPH-Coding
// Create: 2022/9/29
// File: timer.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_TIME_TIMER_H_
#define QWEBSERVER_SRC_TIME_TIMER_H_

#include <sys/timerfd.h>
#include <functional>
#include "../encapsulation/epoll_listener.h"

// TODO
// en:
// Use select instead of epoll
// Because a timer only listen one fd
// In this case, select is more effective than epoll
// zh:
// 使用select代替epoll
// 因为一个计时器只会监听一个fd
// 在这种情况下，select比epoll更加高效

// en:
// use functions about timerfd to time
// have a pure virtual OnTick()
// when time out, will call OnTick() and start timing again
// zh:
// 使用timerfd的系列函数
// 有一个纯虚函数OnTick()
// 当计时结束时，将会调用OnTick()并且再次开始计时
class Timer {
 public:
  explicit Timer(int wait_second) noexcept;
  void Start() noexcept;
  void Stop() noexcept;
  void Reset() noexcept;
  void SetWaitTime(int wait_second) noexcept;
  virtual void OnTick() = 0;
 private:
  EpollListener epoll_listener_;
  int timer_fd_;
  int wait_second_;
  bool is_running_;
};
#endif //QWEBSERVER_SRC_TIME_TIMER_H_
