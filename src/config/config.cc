// Author: QPH-Coding
// Create: 2022/10/3
// File: config.cc
// License: Apache 2.0

#include "config.h"

Config Config::instance_ = Config();

Config::Config() {
  std::ifstream ifs;
  ifs.open(config_path_);
  if (!ifs.is_open()) {
    std::cout << "Error: can not find " << config_path_ << "." << std::endl;
    exit(1);
  }

  Json::Reader reader;
  Json::Value config_json;
  reader.parse(ifs, config_json, false);

  pid_ = getpid();
  server_root_ = config_json["root"].asString();
  server_port_ = config_json["port"].asInt();
  thread_num_ = config_json["thread_num"].asInt();
  sub_reactor_num_ = config_json["sub_reactor_num"].asInt();

  my_sql_init_num_ = config_json["mysql"]["num"].asInt();
  my_sql_host_ = config_json["mysql"]["host"].asString();
  my_sql_port_ = config_json["mysql"]["port"].asUInt();
  my_sql_database_ = config_json["mysql"]["database"].asString();
  my_sql_username_ = config_json["mysql"]["username"].asString();
  my_sql_password_ = config_json["mysql"]["password"].asString();
  ifs.close();
}
const int &Config::MySqlInitNum() {
  return instance_.my_sql_init_num_;
}
const std::string &Config::MySqlHost() {
  return instance_.my_sql_host_;
}
const unsigned int &Config::MySqlPort() {
  return instance_.my_sql_port_;
}
const std::string &Config::MySqlDatabase() {
  return instance_.my_sql_database_;
}
const std::string &Config::MySqlUsername() {
  return instance_.my_sql_username_;
}
const std::string &Config::MySqlPassword() {
  return instance_.my_sql_password_;
}
const int &Config::Port() {
  return instance_.server_port_;
}
const std::string &Config::Root() {
  return instance_.server_root_;
}
const int &Config::ThreadNum() {
  return instance_.thread_num_;
}
const int &Config::SubReactorNum() {
  return instance_.sub_reactor_num_;
}
const int &Config::Pid() {
  return instance_.pid_;
}
const std::string &Config::LogDirPath() {
  return instance_.log_dir_path_;
}
