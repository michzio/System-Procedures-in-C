cmake_minimum_required(VERSION 3.5)
project(Keyboard_Events_in_OS_X)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES main.c keyboard_events.h keyboard_events.c virtual_key_codes.h symbolic_hotkeys.h symbolic_hotkeys.c hotkeys_events.h hotkey_events.c)

add_executable(Keyboard_Events_in_OS_X ${SOURCE_FILES})
target_link_libraries(Keyboard_Events_in_OS_X ${APPLICATION_SERVICES_LIBRARY})