// Author: QPH-Coding
// Create: 2022/9/29
// File: buffer.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_BUFFER_H_
#define QWEBSERVER_SRC_EXPLANATION_BUFFER_H_

#include "../base/uncopyable.h"
#include <vector>
#include <memory>
#include <cstring>

class Buffer : private Uncopyable {
 public:
  explicit Buffer() noexcept;
  bool Append(const char *str, size_t length);
  void Reset() noexcept;
  size_t rest_size() const noexcept;
  size_t size() const noexcept;
  size_t WriteToFd(FILE *fd, size_t length);
 private:
  char buffer_[4096]{};
  size_t read_index_;
  size_t write_index_;
  size_t capacity_ = 4096;
};

#endif //QWEBSERVER_SRC_EXPLANATION_BUFFER_H_