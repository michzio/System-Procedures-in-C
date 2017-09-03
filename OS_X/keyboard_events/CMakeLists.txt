cmake_minimum_required(VERSION 3.6)
project(Keyboard_Events_in_OS_X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/keyboard_events.h src/keyboard_events.c include/virtual_key_codes.h include/symbolic_hot_keys.h src/symbolic_hot_keys.c include/hot_keys_events.h src/hot_keys_events.c)
set(TEST_SOURCE_FILES )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs)
message("building for Apple")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/apple)

### MAKING LIBRARIES ###
# include current project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# mac OS X - Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices)
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)

# subprojects paths
set(AUTOMATION_SCRIPTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../automation_scripts)
set(AUTOMATION_SCRIPTS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../automation_scripts/outputs)

add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${AUTOMATION_SCRIPTS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${AUTOMATION_SCRIPTS_BUILD_DIR} )

# include header files of subprojects
set(COCOA_HELPER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cocoa_helper)
include_directories(${COCOA_HELPER_SRC_DIR}/include)
include_directories(${AUTOMATION_SCRIPTS_SRC_DIR}/include)

# current project shared and static libraries creation
# SHARED
add_library(Keyboard_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Keyboard_Events_Lib Automation_Scripts_Lib)

# STATIC
add_library(Keyboard_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib_Static PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Keyboard_Events_Lib_Static Automation_Scripts_Lib_Static)

### MAKING EXECUTABLE ###
# current project executable creation
add_executable(Keyboard_Events_in_OS_X src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Keyboard_Events_in_OS_X PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_in_OS_X Keyboard_Events_Lib)


# configure_file(resources/default_symbolic_hotkeys.plist resources/default_symbolic_hotkeys.plist COPYONLY)
# configure_file(resources/application_hotkeys.plist resources/application_hotkeys.plist COPYONLY)
# configure_file(resources/system_hotkeys.plist resources/system_hotkeys.plist COPYONLY)

add_custom_command(TARGET Keyboard_Events_in_OS_X POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Keyboard_Events_in_OS_X>/resources)