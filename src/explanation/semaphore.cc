//
// Created by 钱沛桦 on 2022/9/26.
//
#include <iostream>
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