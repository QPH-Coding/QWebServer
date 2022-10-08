#include <iostream>
#include "database/mysql_deal.h"
#include "server/server.h"
#include "utils/utils.h"

int main() {
//  ObjectPool<mysqlpp::Connection> mysql_pool(5, mysql_deal::ConstructConnection, mysql_deal::DestructConnection);
//  MySqlConnectionRaii my_sql_connection_raii(&mysql_pool);
//  mysql_deal::IsUserExist("root", my_sql_connection_raii);
//  mysql_deal::AddUser("user1", "123456", my_sql_connection_raii);
//  bool flag = mysql_deal::CheckUserPassword("user1", "123456", my_sql_connection_raii);
//  if (flag) {
//    std::cout << "right password." << std::endl;
//  }
  QWebServer q_web_server;
  q_web_server.EventLoop();
  return 0;
}
