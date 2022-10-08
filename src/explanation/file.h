// Author: QPH-Coding
// Create: 2022/9/28
// File: file.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_EXPLANATION_FILE_H_
#define QWEBSERVER_SRC_EXPLANATION_FILE_H_

#include <fcntl.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <atomic>
#include <sys/stat.h>
#include <vector>
#include "../explanation/epoll_listener.h"

namespace file {
void SetNonblockSocket(int fd);

std::string ReadNonblockFile(FILE *fd);

bool ReadNonblockFile(int fd, std::string &wait_read);

bool WriteSocket(int socket_fd,
                 const std::string &response_header,
                 const std::vector<char> &response_body);

long GetFileSize(const char *file_path);
}

#endif //QWEBSERVER_SRC_EXPLANATION_FILE_H_
