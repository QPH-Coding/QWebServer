// Author: QPH-Coding
// Create: 2022/10/3
// File: config.cc
// License: Apache 2.0

#include "config.h"

Config Config::instance_ = Config();
//const std::string Config::config_path_ = "/server/config/config.json";
//const std::string Config::log_dir_path_ = "/server/log";

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

  server_port_ = config_json["port"].asInt();

  my_sql_init_num_ = config_json["mysql"]["num"].asInt();
  my_sql_host_ = config_json["mysql"]["host"].asString();
  my_sql_port_ = config_json["mysql"]["port"].asUInt();
  my_sql_database_ = config_json["mysql"]["database"].asString();
  my_sql_username_ = config_json["mysql"]["username"].asString();
  my_sql_password_ = config_json["mysql"]["password"].asString();
  ifs.close();
}
int Config::MySqlInitNum() {
  return instance_.my_sql_init_num_;
}
std::string Config::MySqlHost() {
  return instance_.my_sql_host_;
}
unsigned int Config::MySqlPort() {
  return instance_.my_sql_port_;
}
std::string Config::MySqlDatabase() {
  return instance_.my_sql_database_;
}
std::string Config::MySqlUsername() {
  return instance_.my_sql_username_;
}
std::string Config::MySqlPassword() {
  return instance_.my_sql_password_;
}
int Config::Port() {
  return instance_.server_port_;
}
