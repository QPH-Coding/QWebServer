// Author: QPH-Coding
// Create: 2022/9/29
// File: buffer.cc
// License: Apache 2.0

#include <iostream>
#include "buffer.h"

Buffer::Buffer() noexcept
    : read_index_(0),
      write_index_(0) {
}

bool Buffer::Append(const char *str, size_t length) {
  if (length > rest_size()) {
    return false;
  }
  strcat(buffer_, str);
  write_index_ += length;
  return true;
}

size_t Buffer::rest_size() const noexcept {
  return kCapacity - write_index_ - 1;
}

size_t Buffer::WriteToFd(FILE *fd, size_t length) {
  if (length == 0) {
    return 0;
  }
  fseek(fd, 0, SEEK_END);
  size_t have_write = fwrite(buffer_ + read_index_, sizeof(char), length, fd);
  read_index_ += have_write;
  return have_write;
}

size_t Buffer::size() const noexcept {
  return write_index_ - read_index_;
}

void Buffer::Reset() noexcept {
  memset(buffer_, '\0', kCapacity);
  read_index_ = 0;
  write_index_ = 0;
}
