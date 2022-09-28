// Author: QPH-Coding
// Create: 2022/9/26
// File: semaphore.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_SEMAPHORE_H_
#define QWEBSERVER_SRC_EXPLANATION_SEMAPHORE_H_

#include <semaphore.h>
#include <cassert>

#include "../base/uncopyable.h"

class Semaphore : private Uncopyable {
 public:
  explicit Semaphore(int count = 0) noexcept;
  ~Semaphore() noexcept;
  bool Signal() noexcept;
  bool Wait() noexcept;

 private:
  sem_t sem_;
};

#endif //QWEBSERVER_SRC_EXPLANATION_SEMAPHORE_H_
