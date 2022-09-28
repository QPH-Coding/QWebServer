// Author: QPH-Coding
// Create: 2022/9/26
// File: epoll_listener.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
#define QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
#include <sys/epoll.h>
#include <vector>
#include <atomic>

#include "net.h"
#include "../base/uncopyable.h"

class EpollListener : private Uncopyable {
 public:
  explicit EpollListener(int max_event_num) noexcept;
  void AddEvent(int fd) noexcept;
  ~EpollListener() noexcept;

  std::vector<epoll_event> GetEpollReadyEvents();
 private:
  int max_event_num_;
  epoll_event *epoll_events_;
  int epoll_fd_;
};

#endif //QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
