cmake_minimum_required(VERSION 3.7)
project(keyboard_events)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c keyboard_events.c keyboard_events.h virtual_key_codes.h)
add_executable(keyboard_events ${SOURCE_FILES})