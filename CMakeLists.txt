cmake_minimum_required(VERSION 3.22.1)
project(QWebServer)

set(CMAKE_CXX_STANDARD 20)

set(jsoncpp third_party/jsoncpp/json)
INCLUDE_DIRECTORIES(${jsoncpp})
add_subdirectory(third_party/jsoncpp)

INCLUDE_DIRECTORIES(/usr/include/mysql)
INCLUDE_DIRECTORIES(/usr/include/mysql++)

set(config src/config/config.cc)
set(explanation
        src/explanation/net.cc
        src/explanation/file.cc
        src/log/buffer.cc
        src/explanation/semaphore.cc
        src/explanation/epoll_listener.cc)
set(db src/database/mysql_conn_raii.cc)
set(server src/server/server.cc)

set(time
        src/time/timer.cc
        src/time/time_wheel.cc)
set(http
        src/http/http_connection.cc
        src/http/http_request.cc
        src/http/http_response.cc
        src/http/http_service.cc)

set(log
        src/log/async_log4q.cc)

set(demo
        src/demo/epoll_demo.cc
        src/demo/thread_pool_demo.cc
        src/demo/async_log_demo.cc)

add_executable(QWebServer src/main.cpp
        ${db}
        ${config}
        ${explanation}
        ${time}
        ${log}
        ${server}
        ${http}
        ${demo})

# 链接子工程
target_link_libraries(${PROJECT_NAME} jsoncpp mysqlclient mysqlpp)