// Author: QPH-Coding
// Create: 2022/10/4
// File: mysql_conn_raii.cc
// License: Apache 2.0

#include "mysql_conn_raii.h"

mysqlpp::Connection &MySqlConnectionRaii::get_conn() noexcept {
  return connection_object_.get_object();
}
MySqlConnectionRaii::MySqlConnectionRaii(ObjectPool<mysqlpp::Connection> *mysql_conn_pool) noexcept
    : mysql_conn_pool_(mysql_conn_pool),
      connection_object_(mysql_conn_pool->get_one()) {}

MySqlConnectionRaii::~MySqlConnectionRaii() noexcept {
  mysql_conn_pool_->give_back_one(connection_object_);
  mysql_conn_pool_ = nullptr;
}

