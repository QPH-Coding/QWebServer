cmake_minimum_required(VERSION 3.23)
project(QWebServer)

set(CMAKE_CXX_STANDARD 20)

set(jsoncpp third_party/jsoncpp/json)
INCLUDE_DIRECTORIES(${jsoncpp})
add_subdirectory(third_party/jsoncpp)

INCLUDE_DIRECTORIES(/usr/include/mysql++)

set(explanation
        src/explanation/net.cc
        src/explanation/thread.cc
        src/explanation/semaphore.cc)
set(server src/server/server.cc)
set(pools
        src/pool/thread_pool.cc
        src/pool/mysql_connection_pool.cc
        src/pool/es_connection_pool.cc
        src/pool/task_queue.cc)

add_executable(QWebServer src/main.cpp
        ${explanation}
        ${server}
        ${pools})

# 链接子工程
target_link_libraries(${PROJECT_NAME} jsoncpp)