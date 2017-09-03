cmake_minimum_required(VERSION 3.6)
project(Automation_Scripts_in_OS_X)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/automation_scripts.h src/automation_scripts.c include/system/windows.h src/system/windows.c include/system/events.h src/system/events.c include/system/display.h src/system/display.c include/system/audio.h src/system/audio.c include/system/display_stream.h src/system/display_stream.c)
set(TEST_SOURCE_FILES test/test_display.h test/test_display.c test/test_windows.h test/test_windows.c test/test_system_events.h test/test_system_events.c test/test_audio.h test/test_audio.c test/test_display_stream.h test/test_display_stream.c test/test_automation_scripts.h test/test_automation_scripts.c)

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
find_library(CARBON_LIBRARY Carbon)
find_library(IOKIT_LIBRARY IOKit)
find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
find_library(IOSURFACE_LIBRARY IOSurface)
mark_as_advanced(APPLICATION_SERVICES_LIBRARY CARBON_LIBRARY IOKIT_LIBRARY AUDIO_TOOLBOX_LIBRARY IOSURFACE_LIBRARY)

# OpenCV libraries including
find_package( OpenCV REQUIRED core imgproc highgui)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# custom Cocoa libraries including
set(APPLE_SCRIPT_SYSTEM_AUTOMATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cocoa/AppleScriptSystemAutomation)
add_library(APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB STATIC IMPORTED)
set_target_properties(APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB PROPERTIES IMPORTED_LOCATION ${APPLE_SCRIPT_SYSTEM_AUTOMATION_SRC_DIR}/libAppleScriptSystemAutomation.a)
include_directories(${APPLE_SCRIPT_SYSTEM_AUTOMATION_SRC_DIR}/AppleScriptSystemAutomation)

# subprojects paths
set(COCOA_HELPER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cocoa_helper)
set(COCOA_HELPER_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cocoa_helper/outputs)

# add subprojects
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${COCOA_HELPER_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${COCOA_HELPER_BUILD_DIR} )

# include header files of subprojects
set(COMMON_FUNCTIONS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../common)
set(ZLIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib-1.2.8)
set(LIBPNG_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libpng-1.6.24)
include_directories(${COCOA_HELPER_SRC_DIR}/include)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/include)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/libraries)
include_directories(${ZLIB_SRC_DIR}/include)
include_directories(${LIBPNG_SRC_DIR}/include)

# current project shared and static libraries creation
# SHARED
add_library(Automation_Scripts_Lib SHARED ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_Lib ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${IOSURFACE_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${OpenCV_LIBS})
target_link_libraries(Automation_Scripts_Lib APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB)
target_link_libraries(Automation_Scripts_Lib Cocoa_Helper_Lib)

# STATIC
add_library(Automation_Scripts_Lib_Static ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib_Static PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_Lib_Static ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${IOSURFACE_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${OpenCV_LIBS})
target_link_libraries(Automation_Scripts_Lib_Static APPLE_SCRIPT_SYSTEM_AUTOMATION_LIB)
target_link_libraries(Automation_Scripts_Lib_Static Cocoa_Helper_Lib_Static)

### MAKING EXECUTABLE ###
# copy resources required by executable
file(COPY tools DESTINATION .)
file(COPY tools DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# executable's libraries paths
    set(UNIT_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_tests)
    set(COMPARERS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../comparers)
    # apple
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/apple/libunit_tests.dylib)
    set(COMPARERS_LIB_PATH ${COMPARERS_SRC_DIR}/outputs/lib/apple/libcomparers.dylib)

    # executable's libraries import
    add_library(Unit_Test_Lib SHARED IMPORTED)
    set_target_properties( Unit_Test_Lib PROPERTIES IMPORTED_LOCATION ${UNIT_TESTS_LIB_PATH} )
    add_library(AS_Comparers_Lib SHARED IMPORTED)
    set_target_properties( AS_Comparers_Lib PROPERTIES IMPORTED_LOCATION ${COMPARERS_LIB_PATH} )

# executable's libraries include headers
include_directories( ${UNIT_TESTS_SRC_DIR}/include )
include_directories( ${COMPARERS_SRC_DIR}/include )

# current project executable creation
add_executable(Automation_Scripts_in_OS_X src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Automation_Scripts_in_OS_X PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_in_OS_X Automation_Scripts_Lib)
target_link_libraries(Automation_Scripts_in_OS_X Unit_Test_Lib)
target_link_libraries(Automation_Scripts_in_OS_X AS_Comparers_Lib)
