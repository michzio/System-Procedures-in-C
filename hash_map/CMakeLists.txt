cmake_minimum_required(VERSION 3.5)
project(hash_map)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c hash_map.h hash_map.c)
add_executable(hash_map ${SOURCE_FILES})