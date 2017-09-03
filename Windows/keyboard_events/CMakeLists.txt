cmake_minimum_required(VERSION 3.6)
project(Keyboard_Events_in_Windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/keyboard_events.h src/keyboard_events.c include/virtual_key_codes.h include/hot_keys_events.h src/hot_keys_events.c)
set(TEST_SOURCE_FILES )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs)
message("building for Cygwin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/cygwin)

### MAKING LIBRARIES ###
# include current project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# cygwin libraries including
set(LIBXML2_LIBRARY_PATH /usr/local/lib/)
set(LIBXML2_LIBRARY -L${LIBXML2_LIBRARY_PATH} -lxml2)
include_directories(/usr/local/include/libxml2/)

# subprojects paths
set(MOUSE_EVENTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../mouse_events)
set(MOUSE_EVENTS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../mouse_events/outputs)
set(WINDOWS_HELPERS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../windows_helpers)
set(WINDOWS_HELPERS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../windows_helpers/outputs)

add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${MOUSE_EVENTS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${MOUSE_EVENTS_BUILD_DIR} )

add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${WINDOWS_HELPERS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${WINDOWS_HELPERS_BUILD_DIR} )

# include header files of subprojects
include_directories(${MOUSE_EVENTS_SRC_DIR}/include)
include_directories(${WINDOWS_HELPERS_SRC_DIR}/include)

# copy resources to output directory
configure_file(resources/application_hotkeys.xml resources/application_hotkeys.xml COPYONLY)
configure_file(resources/system_hotkeys.xml resources/system_hotkeys.xml COPYONLY)

# current project shared and static libraries creation
# SHARED
add_library(Keyboard_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib ${LIBXML2_LIBRARY})
target_link_libraries(Keyboard_Events_Lib Mouse_Events_Lib)
target_link_libraries(Keyboard_Events_Lib Windows_Helpers_Lib)

# STATIC
add_library(Keyboard_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib_Static PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib_Static ${LIBXML2_LIBRARY})
target_link_libraries(Keyboard_Events_Lib_Static Mouse_Events_Lib_Static)
target_link_libraries(Keyboard_Events_Lib_Static Windows_Helpers_Lib_Static)

### MAKING EXECUTABLE ###
# current project executable creation
add_executable(Keyboard_Events_in_Windows src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Keyboard_Events_in_Windows PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_in_Windows Keyboard_Events_Lib)