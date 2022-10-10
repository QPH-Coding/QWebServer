// Author: QPH-Coding
// Create: 2022/9/26
// File: config.cc
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_CONFIG_CONFIG_H_
#define QWEBSERVER_SRC_CONFIG_CONFIG_H_

#include <string>
#include <atomic>
#include <fstream>
#include <iostream>
#include "json.h"

class Config {
 public:
  // en: server config
  // zh: 服务器配置
  const static int &Pid();
  const static int &Port();
  const static int &ThreadNum();
  const static int &SubReactorNum();
  const static std::string &Root();
  const static std::string &LogDirPath();

  // en: MySql config
  // zh: MySql配置
  const static int &MySqlInitNum();
  const static std::string &MySqlHost();
  const static unsigned int &MySqlPort();
  const static std::string &MySqlDatabase();
  const static std::string &MySqlUsername();
  const static std::string &MySqlPassword();
 private:
  Config();

  static Config instance_;
  const std::string config_path_ = "/server/config/config.json";
  const std::string log_dir_path_ = "/server/log";

  int pid_;
  int server_port_;
  int thread_num_;
  int sub_reactor_num_;
  std::string server_root_;

  int my_sql_init_num_;
  std::string my_sql_host_;
  unsigned int my_sql_port_;
  std::string my_sql_database_;
  std::string my_sql_username_;
  std::string my_sql_password_;
};

#endif //QWEBSERVER_SRC_CONFIG_CONFIG_H_
