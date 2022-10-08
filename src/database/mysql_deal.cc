// Author: QPH-Coding
// Create: 2022/10/5
// File: mysql_deal.cc
// License: Apache 2.0

#include "mysql_deal.h"

void mysql_deal::ConstructConnection(mysqlpp::Connection &connection) {
  connection.connect(Config::MySqlDatabase().c_str(),
                     Config::MySqlHost().c_str(),
                     Config::MySqlUsername().c_str(),
                     Config::MySqlPassword().c_str(),
                     Config::MySqlPort());
}

void mysql_deal::DestructConnection(mysqlpp::Connection &connection) {
  connection.disconnect();
}

bool mysql_deal::IsUserExist(const std::string &user, MySqlConnectionRaii &my_sql_connection_raii) {
  std::string sql = "SELECT 1 FROM user WHERE name=";
  sql += "'" + user + "' LIMIT 1";
  mysqlpp::Query query = my_sql_connection_raii.get_conn().query(sql);
  std::vector<mysqlpp::Row> rows;
  query.storein(rows);
  if (rows.size() == 1) {
    return true;
  } else {
    return false;
  }
}

bool mysql_deal::CheckUserPassword(const std::string &user,
                                   const std::string &password,
                                   MySqlConnectionRaii &my_sql_connection_raii) {
  std::string sql = "SELECT salt, sha256 FROM user WHERE name=";
  sql += "'" + user + "'";
  mysqlpp::Query query = my_sql_connection_raii.get_conn().query(sql);
  std::vector<mysqlpp::Row> rows;
  query.storein(rows);
  if (rows.size() == 1) {
    mysqlpp::String mysql_salt = rows[0][0];
    mysqlpp::String mysql_sha256 = rows[0][1];
    std::string salt, sha256;
    mysql_salt.to_string(salt);
    mysql_sha256.to_string(sha256);
    std::string check_sha256 = utils::SHA256(password + salt);
    if (check_sha256 == sha256) {
      return true;
    }
  }
  return false;
}

bool mysql_deal::AddUser(const std::string &user,
                         const std::string &password,
                         MySqlConnectionRaii &my_sql_connection_raii) {
  if (IsUserExist(user, my_sql_connection_raii)) {
    return false;
  }
  std::string salt = utils::MakeSalt();
  std::string sha256 = utils::SHA256(password + salt);
  std::string sql = "INSERT INTO user(name, salt, sha256) VALUES";
  sql += "('" + user + "', '" + salt + "', '" + sha256 + "')";
  return my_sql_connection_raii.get_conn().query().exec(sql);
}

bool mysql_deal::ChangePassword(const std::string &user,
                                const std::string &old_password,
                                const std::string &new_password,
                                MySqlConnectionRaii &my_sql_connection_raii) {
  if (!CheckUserPassword(user, old_password, my_sql_connection_raii)) {
    return false;
  }
  std::string salt = utils::MakeSalt();
  std::string sha256 = utils::SHA256(new_password + salt);
  std::string sql = "UPDATE user SET salt='";
  sql += salt + "', sha256='" + sha256 + "' WHERE name='" + user + "'";
  return my_sql_connection_raii.get_conn().query().exec(sql);
}

bool mysql_deal::DeleteUser(const std::string &user,
                            const std::string &password,
                            MySqlConnectionRaii &my_sql_connection_raii) {
  if (!CheckUserPassword(user, password, my_sql_connection_raii)) {
    return false;
  }
  std::string sql = "DELETE FROM user WHERE name='";
  sql += user + "'";
  return my_sql_connection_raii.get_conn().query().exec(sql);
}