// Author: QPH-Coding
// Create: 2022/10/5
// File: utils.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_UTILS_UTILS_H_
#define QWEBSERVER_SRC_UTILS_UTILS_H_

#include <openssl/sha.h>
#include <string>
#include <random>

namespace utils {

const std::string random_character =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*(){}:<>?,./;'[]";

std::string MakeSalt();

std::string SHA256(const std::string &str);
}

#endif //QWEBSERVER_SRC_UTILS_UTILS_H_
