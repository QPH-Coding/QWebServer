//
// Created by 钱沛桦 on 2022/9/19.
//

#ifndef WEBSERVER_THREAD_H
#define WEBSERVER_THREAD_H

#include <pthread.h>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>

namespace thread {
static int thread_id = 0;
}

using workFunc = std::function<void()>;

class Thread {
 public:
  Thread(workFunc& work) noexcept;
  ~Thread() noexcept;

  void join();
  void start();
  pthread_t get_thread_id() const;
  bool is_running() const;

 private:
  static void *_run(void *arg);

  // let copy&operator= private, and use delete(C++11)
  Thread(Thread &) = delete;
  Thread &operator=(Thread &) = delete;

  pthread_t thread_id_;
  bool is_running_;
  workFunc work_;
};

#endif  // WEBSERVER_THREAD_H
