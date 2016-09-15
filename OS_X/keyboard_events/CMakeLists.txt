cmake_minimum_required(VERSION 3.5)
project(Keyboard_Events_in_OS_X)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES main.c keyboard_events.h keyboard_events.c virtual_key_codes.h symbolic_hot_keys.h symbolic_hot_keys.c hot_keys_events.h hot_keys_events.c)
# library paths:
set(COCOA_HELPER_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/cocoa_helper)
set(AUTOMATION_SCRIPTS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/automation_scripts)

configure_file(resources/default_symbolic_hotkeys.plist resources/default_symbolic_hotkeys.plist COPYONLY)
configure_file(resources/application_hotkeys.plist resources/application_hotkeys.plist COPYONLY)
configure_file(resources/system_hotkeys.plist resources/system_hotkeys.plist COPYONLY)

add_executable(Keyboard_Events_in_OS_X ${SOURCE_FILES})
target_link_libraries(Keyboard_Events_in_OS_X ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Keyboard_Events_in_OS_X ${COCOA_HELPER_PATH}/libcocoa_helper.a)
target_link_libraries(Keyboard_Events_in_OS_X ${AUTOMATION_SCRIPTS_PATH}/libautomation_scripts.a)