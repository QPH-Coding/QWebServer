// Author: QPH-Coding
// Create: 2022/9/19
// File: thread.h
// License: Apache 2.0

#ifndef WEBSERVER_THREAD_H
#define WEBSERVER_THREAD_H

#include <pthread.h>
#include <cerrno>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <atomic>

#include "../base/uncopyable.h"

namespace thread {
static pthread_t thread_id = 0;
}

class Thread : private Uncopyable {
 public:
//  typedef std::function<void()> thread_work_func;
//  explicit Thread(thread_work_func &work) noexcept;
//  explicit Thread(thread_work_func &&work) noexcept;

  Thread() noexcept;
  ~Thread() noexcept;

  void Start();
  void Join();
  void Detach();
  virtual void Run() = 0;

  pthread_t get_thread_id() const;
  bool is_running() const;
  bool is_join() const;
  bool is_detach() const;

 private:
  static void *_thread_function(void *arg);

  pthread_t thread_id_;
  bool is_running_;
  bool is_join_;
  bool is_detach_;
//  thread_work_func work_;
};

#endif  // WEBSERVER_THREAD_H
