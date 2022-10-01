// Author: QPH-Coding
// Create: 2022/9/19
// File: thread.cc
// License: Apache 2.0

#include "thread.h"

Thread::Thread() noexcept
    : thread_id_(thread::thread_id++),
      org_thread_id_(thread_id_),
      is_running_(false),
      is_detach_(false),
      is_join_(false) {
}

void Thread::Start() {
  if (is_running_) {
    // TODO log
    return;
  }
  int res = pthread_create(&thread_id_, nullptr, _thread_function, (void *) this);
  if (res != 0) {
    // TODO log
  }
  is_running_ = true;
}

void Thread::Join() {
  if (!is_running_ || is_join_) {
    // TODO log
    return;
  }
  int res = pthread_join(this->thread_id_, nullptr);
  if (res == EDEADLK) {
    std::cout << gettid() << " EDEADLK" << std::endl;
  } else if (res == EINVAL) {
    std::cout << gettid() << " EINVAL" << std::endl;
  } else if (res == ESRCH) {
    std::cout << gettid() << " ESRCH" << std::endl;
  }
//  if (res != 0) {
//    // TODO log
//    std::cout << "thread " << thread_id_ << " Join failed. " << std::endl;
//  }
  is_join_ = true;
}

void Thread::Detach() {
  if (!is_running_ || is_detach_) {
    // TODO log
    return;
  }
  int res = pthread_detach(this->thread_id_);
  if (res != 0) {
    // TODO log
  }
  is_detach_ = true;
}

pthread_t Thread::get_thread_id() const { return thread_id_; }

bool Thread::is_running() const { return is_running_; }

bool Thread::is_join() const { return is_join_; }

bool Thread::is_detach() const { return is_detach_; }

void *Thread::_thread_function(void *arg) {
  auto *thread_ = static_cast<Thread *>(arg);
  thread_->Run();
  return nullptr;
}

Thread::~Thread() {
  if (is_running_) {
    int res = pthread_detach(thread_id_);
  }
}