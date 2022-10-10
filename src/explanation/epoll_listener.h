// Author: QPH-Coding
// Create: 2022/9/26
// File: epoll_listener.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
#define QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_

#include <vector>
#include <atomic>
#include <memory>
#include <sys/epoll.h>
#include "file.h"
#include "../base/uncopyable.h"

class EpollListener : private Uncopyable {
 public:
  explicit EpollListener(int max_event_num) noexcept;
  void AddReadEvent(int fd) const noexcept;
  void ModReadToWriteEvent(int fd) noexcept;
  void RemoveReadEvent(int fd) noexcept;
  void ModWriteToReadEvent(int fd) noexcept;
  ~EpollListener() noexcept;

  std::vector<epoll_event> GetEpollReadyEvents();
 private:
  int max_event_num_;
  std::shared_ptr<epoll_event> epoll_events_;
  int epoll_fd_;
};

#endif //QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
