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

bool file::WriteSocket(int socket_fd,
                       const std::string &response_header,
                       const std::vector<char> &response_body) {
  const char *buffer = response_header.c_str();
  ssize_t have_write = write(socket_fd, buffer, response_header.length());
  if (have_write != response_header.length()) {
    return false;
  }
  char response_body_char[response_body.size()];
  for (int i = 0; i < response_body.size(); ++i) {
    response_body_char[i] = response_body[i];
  }
  size_t write_index = 0, rest_size = response_body.size();
  EpollListener epoll_listener(1);
  epoll_listener.AddWriteEvent(socket_fd);
  while (rest_size > 0) {
    std::vector<epoll_event> epoll_events = epoll_listener.GetEpollReadyEvents();
    if (epoll_events[0].data.fd == socket_fd && epoll_events[0].events & EPOLLOUT) {
      have_write = write(socket_fd, response_body_char + write_index, rest_size);
      if (have_write <= 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
          have_write = 0;
        } else {
          return false;
        }
      } else {
        write_index += have_write;
        rest_size -= have_write;
      }
    }
  }
  return true;
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