//
// Created by 钱沛桦 on 2022/9/26.
//
#include "epoll_demo.h"

void EpollDemo::Test() {
  EpollListener epoll_listener(5);
  epoll_listener.AddReadEvent(STDIN_FILENO);
  int times = 3;
  while (times > 0) {
    std::vector<epoll_event> epoll_events = epoll_listener.GetEpollReadyEvents();
    for (auto v : epoll_events) {
      if (v.data.fd == STDIN_FILENO) {
        std::cout << "Epoll trigger, will trigger " << --times << std::endl;
      }
    }
  }
}
