// Author: QPH-Coding
// Create: 2022/9/29
// File: timer.cc
// License: Apache 2.0

#include <iostream>
#include <semaphore>
#include "timer.h"

Timer::Timer(int wait_second) noexcept
    : epoll_listener_(EpollListener(1)),
      wait_second_(wait_second),
      is_running_(false) {}

void Timer::Start() noexcept {
  timespec now{};
  clock_gettime(CLOCK_REALTIME, &now);
  itimerspec new_value{};
  new_value.it_value.tv_sec = now.tv_sec + wait_second_;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = 0;
  new_value.it_interval.tv_nsec = 0;
  timer_fd_ = timerfd_create(CLOCK_REALTIME, 0);
  epoll_listener_.AddReadEvent(timer_fd_);
  timerfd_settime(timer_fd_, TFD_TIMER_ABSTIME, &new_value, nullptr);
  is_running_ = true;

  while (is_running_) {
    std::cout << gettid() << " start wait epoll" << std::endl;
    std::vector<epoll_event> epoll_events = epoll_listener_.GetEpollReadyEvents();
    for (auto &epoll_event : epoll_events) {
      if (epoll_event.data.fd == timer_fd_) {
        OnTick();
        clock_gettime(CLOCK_REALTIME, &now);
        new_value.it_value.tv_sec = now.tv_sec + wait_second_;
        new_value.it_value.tv_nsec = now.tv_nsec;
        new_value.it_interval.tv_sec = 0;
        new_value.it_interval.tv_nsec = 0;
        timerfd_settime(timer_fd_, TFD_TIMER_ABSTIME, &new_value, nullptr);
      }
    }
  }
}

void Timer::Stop() noexcept {

  epoll_listener_.RemoveEvent(timer_fd_);
  is_running_ = false;
}

void Timer::SetWaitTime(int wait_second) noexcept {
  wait_second_ = wait_second;
}
void Timer::Reset() noexcept {
  // en: stop the timer
  // zh: 停止计时器
  itimerspec new_value{};
  new_value.it_value.tv_sec = 0;
  new_value.it_value.tv_nsec = 0;
  new_value.it_interval.tv_sec = 0;
  new_value.it_interval.tv_nsec = 0;
  timerfd_settime(timer_fd_, TFD_TIMER_ABSTIME, &new_value, nullptr);
  // en: restart timer
  // zh: 重启定时器
  timespec now{};
  clock_gettime(CLOCK_REALTIME, &now);
  new_value.it_value.tv_sec = now.tv_sec + wait_second_;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = 0;
  new_value.it_interval.tv_nsec = 0;
  timerfd_settime(timer_fd_, TFD_TIMER_ABSTIME, &new_value, nullptr);
}

// @TEST
//void Timer::OnTick() {
//  timeval tv_begin{};
//  gettimeofday(&tv_begin, nullptr);
//  std::cout << "on tick " << tv_begin.tv_sec << "." << tv_begin.tv_usec << std::endl;
//}