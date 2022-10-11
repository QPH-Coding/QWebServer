// Author: QPH-Coding
// Create: 2022/9/28
// File: file.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_FILE_H_
#define QWEBSERVER_SRC_EXPLANATION_FILE_H_

#include <fcntl.h>
#include <string>
#include <cstring>
#include <vector>
#include <atomic>
#include <csignal>
#include <sys/socket.h>
#include <sys/stat.h>
#include "../encapsulation/epoll_listener.h"

// en: encapsulate some file and socket read/write operation
// zh: 封装了一些文件和socket的读写操作
namespace file {
void SetNonblockSocket(int fd);

bool ReadNonblockFile(int fd, std::string &wait_read);

long WriteSocket(int socket_fd, const std::vector<char> &buffer);

long GetFileSize(const char *file_path);
}

#endif //QWEBSERVER_SRC_EXPLANATION_FILE_H_
