// Author: QPH-Coding
// Create: 2022/9/26
// File: epoll_listener.cc
// License: Apache 2.0

#include "epoll_listener.h"

EpollListener::EpollListener(int max_event_num) noexcept: max_event_num_(max_event_num) {
  epoll_fd_ = epoll_create(5);
  epoll_events_.reset(new epoll_event[max_event_num_]);
}

EpollListener::~EpollListener() noexcept {
  close(epoll_fd_);
}

void EpollListener::AddReadEvent(int fd) const noexcept {
  epoll_event event{};
  event.events = EPOLLIN | EPOLLET;
  event.data.fd = fd;
  epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event);
  file::SetNonblockSocket(fd);
}

void EpollListener::ModReadToWriteEvent(int fd) noexcept {
  epoll_event event{};
  event.events = EPOLLOUT | EPOLLET;
  event.data.fd = fd;
  epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event);
  file::SetNonblockSocket(fd);
}

void EpollListener::RemoveReadEvent(int fd) noexcept {
  epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, epoll_fd_, nullptr);
}

void EpollListener::ModWriteToReadEvent(int fd) noexcept {
  epoll_event event{};
  event.events = EPOLLIN | EPOLLET;
  event.data.fd = fd;
  epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, epoll_fd_, &event);
}

std::vector<epoll_event> EpollListener::GetEpollReadyEvents() {
  int epoll_ready_num = epoll_wait(epoll_fd_, epoll_events_.get(), max_event_num_, -1);
  if (epoll_ready_num < 0) {
    return {};
  } else {
    return {epoll_events_.get(), epoll_events_.get() + epoll_ready_num};
  }
}

