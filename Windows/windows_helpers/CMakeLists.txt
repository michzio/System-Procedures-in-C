cmake_minimum_required(VERSION 3.6)
project(Windows_Helpers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/windows_helpers/windows.h src/windows_helpers/windows.c)
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
add_library(Windows_Helpers_Lib SHARED ${SOURCE_FILES})
set_target_properties(Windows_Helpers_Lib PROPERTIES OUTPUT_NAME windows_helpers)

# STATIC
add_library(Windows_Helpers_Lib_Static ${SOURCE_FILES})
set_target_properties(Windows_Helpers_Lib_Static PROPERTIES OUTPUT_NAME windows_helpers)

### MAKING EXECUTABLE ###
# current project executable creation
add_executable(Windows_Helpers src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Windows_Helpers PROPERTIES OUTPUT_NAME windows_helpers)
target_link_libraries(Windows_Helpers Windows_Helpers_Lib)