// Author: QPH-Coding
// Create: 2022/10/5
// File: mysql_deal.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_
#define QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_

#include "mysql_conn_raii.h"
#include "../config/config.h"
#include "../utils/utils.h"

// en:
// Deal with MySql operation
// operate the user
// zh:
// 处理MySql操作
// 主要是处理用户相关的操作
namespace mysql_deal {

void ConstructConnection(mysqlpp::Connection &connection);

void DestructConnection(mysqlpp::Connection &connection);

bool IsUserExist(const std::string &user, MySqlConnectionRaii &my_sql_connection_raii);

bool CheckUserPassword(const std::string &user,
                       const std::string &password,
                       MySqlConnectionRaii &my_sql_connection_raii);

bool AddUser(const std::string &user,
             const std::string &password,
             MySqlConnectionRaii &my_sql_connection_raii);

bool ChangePassword(const std::string &user,
                    const std::string &old_password,
                    const std::string &new_password,
                    MySqlConnectionRaii &my_sql_connection_raii);

bool DeleteUser(const std::string &user,
                const std::string &password,
                MySqlConnectionRaii &my_sql_connection_raii);
}

#endif //QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_
