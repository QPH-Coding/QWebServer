//
// Created by 钱沛桦 on 2022/9/26.
//

#ifndef QWEBSERVER_SRC_CONFIG_CONFIG_H_
#define QWEBSERVER_SRC_CONFIG_CONFIG_H_
#include <string>

namespace config {
const static int kPort = 8080;

// TODO change dir
const static std::string kLogPath = "/server/log";
const static int kPid = getpid();

const static std::string kMySqlUsername = "";
const static std::string KMySqlPassword = "";

const static std::string kESUsername = "";
const static std::string kESPassword = "";
}

#endif //QWEBSERVER_SRC_CONFIG_CONFIG_H_
