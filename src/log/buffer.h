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

// TODO
// en:
// The reason I design this class is for AsyncLogSystem
// In fact, it can design a more usable class
// zh:
// 我设计这个类的原因是为了给异步日志系统使用
// 实际上，他可以设计成可复用性更高的类

// en:
// default size is 2 MB
// only the AsyncLog use
// zh:
// 默认的大小为 2 MB
// 只有异步日志系统使用
class Buffer : private Uncopyable {
 public:
  explicit Buffer() noexcept;
  bool Append(const char *str, size_t length);
  void Reset() noexcept;
  size_t rest_size() const noexcept;
  size_t size() const noexcept;
  size_t WriteToFd(FILE *fd, size_t length);
 private:
  static const size_t kCapacity = 2 * 1024 * 1024; // 2 MB
  char buffer_[kCapacity]{};
  size_t read_index_;
  size_t write_index_;
};

#endif //QWEBSERVER_SRC_EXPLANATION_BUFFER_H_
