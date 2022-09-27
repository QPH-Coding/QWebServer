//
// Created by 钱沛桦 on 2022/9/26.
//
#include "epoll_listener.h"

EpollListener::EpollListener(int max_event_num) noexcept: max_event_num_(max_event_num) {
  this->epoll_fd_ = epoll_create(5);
  epoll_events_ = new epoll_event[max_event_num_];
}

EpollListener::~EpollListener() noexcept {
  delete[] epoll_events_;
  close(epoll_fd_);
}

void EpollListener::AddEvent(int fd) noexcept {
  epoll_event event{};
  event.events = EPOLLIN | EPOLLET;
  event.data.fd = fd;
  epoll_ctl(this->epoll_fd_, EPOLL_CTL_ADD, fd, &event);
  net::SetNonblockSocket(fd);
}

std::vector<epoll_event> EpollListener::GetEpollReadyEvents() {
  int epoll_ready_num = epoll_wait(this->epoll_fd_, this->epoll_events_, max_event_num_, -1);
  if (epoll_ready_num < 0) {
    // TODO log-error
    std::cout << "Epoll failed." << std::endl;
    return {};
  } else {
    return {this->epoll_events_, this->epoll_events_ + epoll_ready_num};
  }
}