// Author: QPH-Coding
// Create: 2022/9/28
// File: file.cc
// License: Apache 2.0

#include "file.h"

void file::SetNonblockSocket(int fd) {
  int flag = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

std::string file::ReadNonblockFile(FILE *fd) {
  char buffer[1024];
  int read_index = 0;
  std::string res_str;
  while (true) {
    memset(buffer, '\0', 1024);
    int have_read = fread(buffer + read_index, sizeof(char), 1024, fd);
    read_index += have_read;
    if (have_read <= 0) {
      break;
    } else {
      res_str += buffer;
    }
  }
  return res_str;
}

bool file::WriteSocket(int socket_fd, const std::string &wait_write_str) {
  const char *buffer = wait_write_str.c_str();
  int have_write = write(socket_fd, buffer, wait_write_str.length());
  if (have_write == wait_write_str.length()) {
    return true;
  } else {
    return false;
  }
}

bool file::ReadNonblockFile(int fd, std::string &wait_read) {
  char buffer[1024];
  while (true) {
    memset(buffer, '\0', 1024);
    int have_read = recv(fd, buffer, sizeof(buffer), 0);
    if (have_read <= 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        return true;
      }
      return false;
    } else {
      wait_read += buffer;
    }
  }
}