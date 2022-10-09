// Author: QPH-Coding
// Create: 2022/10/5
// File: utils.cc
// License: Apache 2.0

#include "utils.h"

std::string utils::MakeSalt() {
  std::default_random_engine e(time(nullptr));
  std::uniform_int_distribution<unsigned> u(0, random_character.length());
  std::string salt;
  for (int i = 0; i < 6; ++i) {
    salt += random_character[u(e)];
  }
  return salt;
}

std::string utils::SHA256(const std::string &str) {
  char buf[2];
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  std::string new_string;
  for (unsigned char i : hash) {
    sprintf(buf, "%02x", i);
    new_string = new_string + buf;
  }
  return new_string;
}