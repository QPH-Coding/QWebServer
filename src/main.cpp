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

class BenchThread : public Thread {
 public:
  void Run() override {
    for (int i = 0; i < 100; ++i) {
      AsyncLog4Q::Info("Thread tset");
    }
  }
};

int main() {
//  ThreadPoolDemo thread_pool_demo;
//  thread_pool_demo.Test();
//  EpollDemo epoll_demo;
//  epoll_demo.Test();

//  AsyncLog4Q::Warn("asfasf");
//  for (int i = 0; i < 5; ++i) {
//    BenchThread bench_thread;
//    bench_thread.Start();
//    bench_thread.Detach();
//  }
  while (true) {}
//  TimerTest test(2);
//  test.Start();
  return 0;
}
