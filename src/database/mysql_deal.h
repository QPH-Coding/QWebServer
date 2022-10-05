// Author: QPH-Coding
// Create: 2022/10/5
// File: mysql_deal.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_
#define QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_
#include "mysql_conn_raii.h"
#include "../config/config.h"
#include "../utils/utils.h"

namespace mysql_deal {

void ConstructConnection(mysqlpp::Connection &connection);

void DestructConnection(mysqlpp::Connection &connection);

bool IsUserExist(const std::string &user, MySqlConnectionRaii &my_sql_connection_raii);

bool CheckUserPassword(const std::string &user,
                       const std::string &password,
                       MySqlConnectionRaii &my_sql_connection_raii);

bool AddUser(const std::string &user, const std::string &password, MySqlConnectionRaii &my_sql_connection_raii);

}

#endif //QWEBSERVER_SRC_DATABASE_MYSQL_DEAL_H_
