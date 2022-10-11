// Author: QPH-Coding
// Create: 2022/9/26
// File: semaphore.cc
// License: Apache 2.0

#include "semaphore.h"

Semaphore::Semaphore(int num) noexcept {
  int res = sem_init(&sem_, 0, num);
  assert(res == 0);
}

Semaphore::~Semaphore() noexcept {
  sem_destroy(&sem_);
}

bool Semaphore::Signal() noexcept {
  return sem_post(&sem_) == 0;
}

bool Semaphore::Wait() noexcept {
  return sem_wait(&sem_) == 0;
}