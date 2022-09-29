// Author: QPH-Coding
// Create: 2022/9/29
// File: buffer.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_BUFFER_H_
#define QWEBSERVER_SRC_EXPLANATION_BUFFER_H_

#include "../base/uncopyable.h"
#include <vector>
#include <memory>

class Buffer : private Uncopyable {
 public:
  void append(const char *string, int length);
  int size() const noexcept;
 private:
  std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[2048]);
  int read_index_;
  int write_index;
};

#endif //QWEBSERVER_SRC_EXPLANATION_BUFFER_H_
