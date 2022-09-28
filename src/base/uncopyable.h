// Author: QPH-Coding
// Create: 2022/9/27
// File: uncopyable.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_BASE_UNCOPYABLE_H_
#define QWEBSERVER_SRC_BASE_UNCOPYABLE_H_
class Uncopyable {
 public:
  Uncopyable() = default;
  Uncopyable(const Uncopyable &) = delete;
  Uncopyable(const Uncopyable &&) = delete;
  Uncopyable &operator=(const Uncopyable &) = delete;
  Uncopyable &operator=(const Uncopyable &&) = delete;
  ~Uncopyable() = default;
};

#endif //QWEBSERVER_SRC_BASE_UNCOPYABLE_H_
