cmake_minimum_required(VERSION 3.6)
project(Automation_Scripts)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES automation_scripts.h automation_scripts.c system/windows.h system/windows.c system/events.h system/events.c system/display.h system/display.c system/audio.h system/audio.c system/display_stream.h system/display_stream.c)
set(TEST_SOURCE_FILES test/test_display.h test/test_display.c test/test_windows.h test/test_windows.c test/test_system_events.h test/test_system_events.c test/test_audio.h test/test_audio.c test/test_display_stream.h test/test_display_stream.c test/test_automation_scripts.h test/test_automation_scripts.c)

# OS X Cocoa libraries including
find_library(CARBON_LIBRARY Carbon)
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices)
find_library(IOKIT_LIBRARY IOKit)
find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
find_library(IOSURFACE_LIBRARY IOSurface)
mark_as_advanced(CARBON_LIBRARY APPLICATION_SERVICES_LIBRARY IOKIT_LIBRARY AUDIO_TOOLBOX_LIBRARY IOSURFACE_LIBRARY)

# OpenCV library including
find_package( OpenCV REQUIRED core imgproc highgui)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# libraries paths
set(COMMON_FUNCTIONS_PATH ${CMAKE_SOURCE_DIR}/../../../common)
set(LIBPNG_PATH ${CMAKE_SOURCE_DIR}/../../../libpng-1.6.24)
set(ZLIB_PATH ${CMAKE_SOURCE_DIR}/../../../zlib-1.2.8)
set(COMPARERS_PATH ${CMAKE_SOURCE_DIR}/../../../comparers)
set(UNIT_TESTS_PATH ${CMAKE_SOURCE_DIR}/../../../unit_tests)

set(COMMON_FUNCTIONS_LIB_PATH ${COMMON_FUNCTIONS_PATH}/output/unix/lib/static/libcommon_functions.a)
set(LIBPNG_LIB_PATH ${LIBPNG_PATH}/output/unix/lib/static/liblibpng.a)
set(ZLIB_LIB_PATH ${ZLIB_PATH}/output/unix/lib/static/libzlib.a)
set(COMPARERS_LIB_PATH ${COMPARERS_PATH}/output/unix/lib/static/libcomparers.a)
set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_PATH}/output/unix/lib/static/libunit_tests.a)

# custom cocoa libraries paths
set(COCOA_HELPER_PATH ${CMAKE_SOURCE_DIR}/../cocoa_helper)
set(APPLE_SCRIPT_SYSTEM_AUTOMATION_PATH ${CMAKE_SOURCE_DIR}/../../../../cocoa/AppleScriptSystemAutomation)

set(COCOA_HELPER_LIB_PATH ${COCOA_HELPER_PATH}/output/apple/lib/static/libcocoa_helper.a)
set(APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB_PATH ${APPLE_SCRIPT_SYSTEM_AUTOMATION_PATH}/libAppleScriptSystemAutomation.a)

file(COPY tools DESTINATION .)

add_library(Automation_Scripts_Lib SHARED ${SOURCE_FILES} system/display_stream.c)
set_target_properties(Automation_Scripts_Lib PROPERTIES OUTPUT_NAME automation_scripts_shared)
target_link_libraries(Automation_Scripts_Lib ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib ${LIBPNG_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib ${ZLIB_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib ${COCOA_HELPER_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib ${APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${IOSURFACE_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${OpenCV_LIBS})

add_library(Automation_Scripts_Lib_Static ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib_Static PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_Lib_Static ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib_Static ${LIBPNG_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib_Static ${ZLIB_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib_Static ${COCOA_HELPER_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib_Static ${APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB_PATH})
target_link_libraries(Automation_Scripts_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${IOSURFACE_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${OpenCV_LIBS})

add_executable(Automation_Scripts_in_OS_X main.c ${TEST_SOURCE_FILES})
set_target_properties(Automation_Scripts_in_OS_X PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_in_OS_X Automation_Scripts_Lib_Static)
target_link_libraries(Automation_Scripts_in_OS_X ${COMPARERS_LIB_PATH})
target_link_libraries(Automation_Scripts_in_OS_X ${UNIT_TESTS_LIB_PATH})

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

# apple
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib/static)

install(TARGETS Automation_Scripts_in_OS_X Automation_Scripts_Lib Automation_Scripts_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})