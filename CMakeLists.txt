cmake_minimum_required(VERSION 3.23)
project(QWebServer)

set(CMAKE_CXX_STANDARD 20)

set(jsoncpp third_party/jsoncpp/json)
INCLUDE_DIRECTORIES(${jsoncpp})
add_subdirectory(third_party/jsoncpp)

INCLUDE_DIRECTORIES(/usr/include/mysql++ /usr/include/mysql)

set(explanation
        src/explanation/net.cc
        src/explanation/file.cc
        src/explanation/buffer.cc
        src/explanation/thread.cc
        src/explanation/semaphore.cc
        src/explanation/epoll_listener.cc)
set(server src/server/server.cc)

set(time
        src/time/timer.cc)
set(http
        src/http/http_connection.cc)
set(demo
        src/demo/epoll_demo.cc
        src/demo/thread_pool_demo.cc)

add_executable(QWebServer src/main.cpp
        ${explanation}
        ${time}
        ${server}
        ${http}
        ${demo})

# 链接子工程
target_link_libraries(${PROJECT_NAME} jsoncpp pthread)