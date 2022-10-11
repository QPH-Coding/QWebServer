// Author: QPH-Coding
// Create: 2022/9/28
// File: file.cc
// License: Apache 2.0

#include "file.h"

void file::SetNonblockSocket(int fd) {
  int flag = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

long file::WriteSocket(int socket_fd, const std::vector<char> &buffer) {
//  signal(SIGPIPE, SIG_IGN);
  char c_buffer[buffer.size()];
  for (long i = 0; i < buffer.size(); ++i) {
    c_buffer[i] = buffer[i];
  }
  long have_write = write(socket_fd, c_buffer, buffer.size());
  return have_write;
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

long file::GetFileSize(const char *file_path) {
  struct stat file_status{};
  stat(file_path, &file_status);
  return file_status.st_size;
}