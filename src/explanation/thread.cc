//
// Created by 钱沛桦 on 2022/9/26.
//
#include "thread.h"

Thread::Thread(workFunc& work) noexcept
    : thread_id_(thread::thread_id++),
      is_running_(false),
      work_(std::move(work)) {}

void Thread::start() {
  if (work_ == nullptr) {
  }
  int res = pthread_create(&thread_id_, nullptr, _run, (void *) this);
  if (res != 0) {
    // TODO log
  }
  is_running_ = true;
}

void Thread::join() {
  int res = pthread_join(thread_id_, nullptr);
  if (res != 0) {
    // TODO log
  }
}

pthread_t Thread::get_thread_id() const { return thread_id_; }
bool Thread::is_running() const { return is_running_; }

void *Thread::_run(void *arg) {
  auto *thread_ = static_cast<Thread *>(arg);
  thread_->work_();
  return nullptr;
}

Thread::~Thread() {
  if (is_running_) {
    int res = pthread_detach(thread_id_);
  }
}