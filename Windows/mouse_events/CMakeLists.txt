cmake_minimum_required(VERSION 3.6)
project(Mouse_Events_in_Windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/mouse_events.h src/mouse_events.c include/scroll_wheel_events.h src/scroll_wheel_events.c)
set(TEST_SOURCE_FILES )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs)
message("building for Cygwin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/cygwin)

### MAKING LIBRARIES ###
# include current project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# current project shared and static libraries creation
# SHARED
add_library(Mouse_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Mouse_Events_Lib PROPERTIES OUTPUT_NAME mouse_events)

# STATIC
add_library(Mouse_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Mouse_Events_Lib_Static PROPERTIES OUTPUT_NAME mouse_events)

### MAKING EXECUTABLE ###
# current project executable creation
add_executable(Mouse_Events_in_Windows src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Mouse_Events_in_Windows PROPERTIES OUTPUT_NAME mouse_events)
target_link_libraries(Mouse_Events_in_Windows Mouse_Events_Lib)
