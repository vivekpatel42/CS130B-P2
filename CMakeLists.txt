cmake_minimum_required(VERSION 3.3)
project(CS130B_P2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CS130B_P2 ${SOURCE_FILES})