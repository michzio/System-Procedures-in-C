cmake_minimum_required(VERSION 3.5)
project(exec_cmd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES exec_cmd.c)
add_executable(exec_cmd ${SOURCE_FILES})