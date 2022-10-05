//
// Created by 钱沛桦 on 2022/9/26.
//

#ifndef QWEBSERVER_SRC_CONFIG_CONFIG_H_
#define QWEBSERVER_SRC_CONFIG_CONFIG_H_
#include <string>
#include <atomic>
#include <fstream>
#include <iostream>
#include "json.h"

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

class Config {
 public:
//  static std::string LogDirPath();

  static int Port();

  static int MySqlInitNum();
  static std::string MySqlHost();
  static unsigned int MySqlPort();
  static std::string MySqlDatabase();
  static std::string MySqlUsername();
  static std::string MySqlPassword();
 private:
  Config();

  static Config instance_;
  const std::string config_path_ = "/server/config/config.json";
  const std::string log_dir_path_ = "/server/log";

  int server_port_;

  int my_sql_init_num_;
  std::string my_sql_host_;
  unsigned int my_sql_port_;
  std::string my_sql_database_;
  std::string my_sql_username_;
  std::string my_sql_password_;

//  std::string elastic_search_url_;
//  std::string elastic_search_username_;
//  std::string elastic_search_password_;
};

#endif //QWEBSERVER_SRC_CONFIG_CONFIG_H_
