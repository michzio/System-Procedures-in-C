cmake_minimum_required(VERSION 3.6)
project(Mouse_Events_in_Windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES mouse_events.h mouse_events.c)
set(TEST_SOURCE_FILES )

# libraries paths
# none

add_library(Mouse_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Mouse_Events_Lib PROPERTIES OUTPUT_NAME mouse_events_shared)

add_library(Mouse_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Mouse_Events_Lib_Static PROPERTIES OUTPUT_NAME mouse_events)

add_executable(Mouse_Events_in_Windows main.c ${TEST_SOURCE_FILES})
set_target_properties(Mouse_Events_in_Windows PROPERTIES OUTPUT_NAME mouse_events)
target_link_libraries(Mouse_Events_in_Windows Mouse_Events_Lib_Static)

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

# windows cygwin
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib/static)

install(TARGETS Mouse_Events_in_Windows Mouse_Events_Lib Mouse_Events_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})