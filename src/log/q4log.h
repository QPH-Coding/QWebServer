// Author: QPH-Coding
// Create: 2022/9/28
// File: q4log.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_LOG_Q4LOG_H_
#define QWEBSERVER_SRC_LOG_Q4LOG_H_

class Q4Log {
 public:
  enum class Level {
    Debug = 0, Info = 1, Warn = 2, Error = 3
  };

 private:
  Level log_level_;
  bool is_allow_;
};

#endif //QWEBSERVER_SRC_LOG_Q4LOG_H_
