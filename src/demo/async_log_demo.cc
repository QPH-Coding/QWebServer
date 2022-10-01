// Author: QPH-Coding
// Create: 2022/10/1
// File: async_log_demo.cc
// License: Apache 2.0
#include "async_log_demo.h"

void BenchLog() {
  for (int i = 0; i < 50; ++i) {
    std::string str = "Thread test ";
    str += std::to_string(i);
    AsyncLog4Q::Info(str);
  }
}
void AsyncLogDemo() {
  std::thread thread_1(BenchLog);
  thread_1.detach();
  std::thread thread_2(BenchLog);
  thread_2.detach();
}
