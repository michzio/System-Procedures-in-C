cmake_minimum_required(VERSION 3.6)
project(Keyboard_Events_in_OS_X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES keyboard_events.h keyboard_events.c virtual_key_codes.h symbolic_hot_keys.h symbolic_hot_keys.c hot_keys_events.h hot_keys_events.c)
set(TEST_SOURCE_FILES )

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices)
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)

# library paths
# none

# custom cocoa libraries paths
set(COCOA_HELPER_PATH ${CMAKE_SOURCE_DIR}/../cocoa_helper)
set(AUTOMATION_SCRIPTS_PATH ${CMAKE_SOURCE_DIR}/../automation_scripts)

set(COCOA_HELPER_LIB_PATH ${COCOA_HELPER_PATH}/output/apple/lib/static/libcocoa_helper.a)
set(AUTOMATION_SCRIPTS_LIB_PATH ${AUTOMATION_SCRIPTS_PATH}/output/apple/lib/static/libautomation_scripts.a)

configure_file(resources/default_symbolic_hotkeys.plist resources/default_symbolic_hotkeys.plist COPYONLY)
configure_file(resources/application_hotkeys.plist resources/application_hotkeys.plist COPYONLY)
configure_file(resources/system_hotkeys.plist resources/system_hotkeys.plist COPYONLY)

add_library(Keyboard_Events_Lib SHARED ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib ${COCOA_HELPER_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib ${AUTOMATION_SCRIPTS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib ${APPLICATION_SERVICES_LIBRARY})

add_library(Keyboard_Events_Lib_Static ${SOURCE_FILES})
set_target_properties(Keyboard_Events_Lib_Static PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_Lib_Static ${COCOA_HELPER_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib_Static ${AUTOMATION_SCRIPTS_LIB_PATH})
target_link_libraries(Keyboard_Events_Lib_Static ${APPLICATION_SERVICES_LIBRARY})

add_executable(Keyboard_Events_in_OS_X main.c ${TEST_SOURCE_FILES})
set_target_properties(Keyboard_Events_in_OS_X PROPERTIES OUTPUT_NAME keyboard_events)
target_link_libraries(Keyboard_Events_in_OS_X Keyboard_Events_Lib_Static)

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

# apple
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib/static)

install(TARGETS Keyboard_Events_in_OS_X Keyboard_Events_Lib Keyboard_Events_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})