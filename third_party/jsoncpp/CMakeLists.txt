CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)

project(jsoncpp)
add_library(${PROJECT_NAME} jsoncpp.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
