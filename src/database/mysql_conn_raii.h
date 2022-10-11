// Author: QPH-Coding
// Create: 2022/10/4
// File: mysql_conn_raii.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_DATABASE_MYSQL_CONN_RAII_H_
#define QWEBSERVER_SRC_DATABASE_MYSQL_CONN_RAII_H_

#include <mysql++.h>
#include "../config/config.h"
#include "../pool/object_pool.hpp"

// en:
// Use RAII get MySql connection from Object Pool(MySql Connection Pool)
// zh:
// 用RAII的处理从对象池(MySql连接池)获取MySql连接
class MySqlConnectionRaii {
 public:
  explicit MySqlConnectionRaii(ObjectPool<mysqlpp::Connection> *mysql_conn_pool) noexcept;
  mysqlpp::Connection &get_conn() noexcept;
  ~MySqlConnectionRaii() noexcept;
 private:
  Object<mysqlpp::Connection> connection_object_;
  ObjectPool<mysqlpp::Connection> *mysql_conn_pool_;
};

#endif //QWEBSERVER_SRC_DATABASE_MYSQL_CONN_RAII_H_
