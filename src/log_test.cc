// Author: QPH-Coding
// Create: 2022/10/12
// File: log_test.cc
// License: Apache 2.0

#include "log/async_log4q.h"

class LogTimer : public Timer {
 public:
  LogTimer(int second);
  void OnTick() override {
    AsyncLog4Q_Info("This a test " + std::to_string(num));
    ++num;
  }
 private:
  int num;
};

LogTimer::LogTimer(int second) : Timer(second), num(0) {}

int main() {
  for (int i = 0; i < 15; ++i) {
    LogTimer log_timer(1);
    std::thread log_thread([&] { log_timer.Start(); });
    log_thread.detach();
  }
  while (true) {}
}