//
// Created by 钱沛桦 on 2022/9/26.
//

#ifndef QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
#define QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
#include <sys/epoll.h>
#include <vector>

#include "net.h"

class EpollListener {
 public:
  EpollListener(int max_event_num) noexcept;
  void AddEvent(int fd) noexcept;
  ~EpollListener() noexcept;

  std::vector<epoll_event> GetEpollReadyEvents();
 private:
  int max_event_num_;
  epoll_event *epoll_events_;
  int epoll_fd_;
};

#endif //QWEBSERVER_SRC_EXPLANATION_EPOLL_LISTENER_H_
