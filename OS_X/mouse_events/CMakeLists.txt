cmake_minimum_required(VERSION 3.5)
project(Mouse_Events_in_OS_X)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES main.c mouse_events.h mouse_events.c scroll_wheel_events.h scroll_wheel_events.c)

add_executable(Mouse_Events_in_OS_X ${SOURCE_FILES})
target_link_libraries(Mouse_Events_in_OS_X ${APPLICATION_SERVICES_LIBRARY} )