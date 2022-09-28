// Author: QPH-Coding
// Create: 2022/9/28
// File: file.cc
// License: Apache 2.0

#include "file.h"

void file::SetNonblockSocket(int fd) {
  int flag = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}