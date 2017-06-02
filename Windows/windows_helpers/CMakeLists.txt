cmake_minimum_required(VERSION 3.6)
project(Windows_Helpers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES windows.h windows.c)
set(TEST_SOURCE_FILES )

# libraries paths
# nothing

add_library(Windows_Helpers_Lib SHARED ${SOURCE_FILES})
set_target_properties(Windows_Helpers_Lib PROPERTIES OUTPUT_NAME windows_helpers_shared)

add_library(Windows_Helpers_Lib_Static ${SOURCE_FILES})
set_target_properties(Windows_Helpers_Lib_Static PROPERTIES OUTPUT_NAME windows_helpers)

add_executable(Windows_Helpers main.c ${TEST_SOURCE_FILES})
set_target_properties(Windows_Helpers PROPERTIES OUTPUT_NAME windows_helpers)
target_link_libraries(Windows_Helpers Windows_Helpers_Lib_Static)

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

# only windows cygwin
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib/static)

install(TARGETS Windows_Helpers Windows_Helpers_Lib Windows_Helpers_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})