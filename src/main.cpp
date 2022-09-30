#include <iostream>
#include "demo/epoll_demo.h"
#include "demo/thread_pool_demo.h"
#include "time/timer.h"
#include "log/async_log4q.h"

class TimerTest : public Timer {
 public:
  TimerTest(int second) noexcept;
  void OnTick() override;
};

void TimerTest::OnTick() {
  std::cout << "tick" << std::endl;
}
TimerTest::TimerTest(int second) noexcept: Timer(second) {

}

int main() {
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
//  EpollDemo epoll_demo;
//  epoll_demo.Test();

  AsyncLog4Q::Info("hello world");
  while (true) {}
//  TimerTest test(2);
//  test.Start();
  return 0;
}
