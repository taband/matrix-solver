cmake_minimum_required(VERSION 3.0)
project(hello)
set(CMAKE_CXX_COMPILER g++)
set(SOURCES src/hello.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})