cmake_minimum_required(VERSION 3.6)
project(Keyboard_Events_in_Windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES keyboard_events.h keyboard_events.c virtual_key_codes.h hot_keys_events.h hot_keys_events.c)
set(TEST_SOURCE_FILES )

# copy resources to output directory
configure_file(resources/application_hotkeys.xml resources/application_hotkeys.xml COPYONLY)
configure_file(resources/system_hotkeys.xml resources/system_hotkeys.xml COPYONLY)

# libraries paths
set(MOUSE_EVENTS_PATH ${CMAKE_SOURCE_DIR}/../mouse_events)
set(WINDOWS_HELPERS_PATH ${CMAKE_SOURCE_DIR}/../windows_helpers)
set(LIBXML2_LIBRARY_PATH /usr/local/lib/)

set(MOUSE_EVENTS_LIB_PATH ${MOUSE_EVENTS_PATH}/output/windows/lib/static/libmouse_events.a)
set(WINDOWS_HELPERS_LIB_PATH ${WINDOWS_HELPERS_PATH}/output/windows/lib/static/libwindows_helpers.a)
set(LIBXML2_LIBRARIES -L${LIBXML2_LIBRARY_PATH} -lxml2)

# include directories
# LIBXML 2
include_directories(/usr/local/include/libxml2/)

add_library(Keyboard_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib PROPERTIES OUTPUT_NAME keyboard_events_shared)
target_link_libraries(Keyboard_Events_Lib ${MOUSE_EVENTS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib ${WINDOWS_HELPERS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib ${LIBXML2_LIBRARIES})

add_library(Keyboard_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib_Static PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib_Static ${MOUSE_EVENTS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib_Static ${WINDOWS_HELPERS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib_Static ${LIBXML2_LIBRARIES})

add_executable(Keyboard_Events_in_Windows main.c ${TEST_SOURCE_FILES})
set_target_properties(Keyboard_Events_in_Windows PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_in_Windows Keyboard_Events_Lib_Static)

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                $(MAKE) install
                DEPENDS ${PROJECT_NAME}
                COMMENT "Installing ${PROJECT_NAME}")

# only windows cygwin
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib/static)

install(TARGETS Keyboard_Events_in_Windows Keyboard_Events_Lib Keyboard_Events_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})