// Author: QPH-Coding
// Create: 2022/10/3
// File: config.cc
// License: Apache 2.0

#include "config.h"

Config Config::instance_ = Config();
const std::string Config::config_path_ = "/server/config";
const std::string Config::log_dir_path_ = "/server/log";

Config::Config() {
//  std::ifstream ifs;
//  ifs.open(config_path_);
//  if (!ifs.is_open()) {
//    std::cout << "Error: can not find " << config_path_ << "." << std::endl;
//    exit(1);
//  }
//
//  Json::Reader reader;
//  Json::Value config_json;
//  reader.parse(ifs, config_json, false);
//  ifs.close();

}
