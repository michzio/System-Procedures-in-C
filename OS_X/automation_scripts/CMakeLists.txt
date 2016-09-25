cmake_minimum_required(VERSION 3.5)
project(automation_scripts)
set(CMAKE_VERBOSE_MAKEFILE ON)

# OS X Cocoa libraries including
find_library(CARBON_LIBRARY Carbon)
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices)
find_library(IOKIT_LIBRARY IOKit)
find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
mark_as_advanced(CARBON_LIBRARY APPLICATION_SERVICES_LIBRARY IOKIT_LIBRARY AUDIO_TOOLBOX_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES automation_scripts.h automation_scripts.c system/windows.h system/windows.c system/events.h system/events.c system/display.h system/display.c system/audio.h system/audio.c)
# libraries paths
set(COCOA_HELPER_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/cocoa_helper)
set(COMMON_FUNCTIONS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/common)

file(COPY tools DESTINATION .)

add_library(Automation_Scripts_Lib SHARED ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib PROPERTIES OUTPUT_NAME automation_scripts_shared)
target_link_libraries(Automation_Scripts_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${COCOA_HELPER_PATH}/libcocoa_helper.a)
target_link_libraries(Automation_Scripts_Lib ${COMMON_FUNCTIONS_PATH}/libcommon_functions.a)

add_library(Automation_Scripts_Lib_Static ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib_Static PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${CARBON_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${IOKIT_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${AUDIO_TOOLBOX_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${COCOA_HELPER_PATH}/libcocoa_helper.a)
target_link_libraries(Automation_Scripts_Lib_Static ${COMMON_FUNCTIONS_PATH}/libcommon_functions.a)

add_executable(Automation_Scripts_in_OS_X main.c)
target_link_libraries(Automation_Scripts_in_OS_X Automation_Scripts_Lib_Static)
# additional links are not needed if we are linking with static library:
#target_link_libraries(Automation_Scripts_in_OS_X ${APPLICATION_SERVICES_LIBRARY})
#target_link_libraries(Automation_Scripts_in_OS_X ${COCOA_HELPER_PATH}/libcocoa_helper.a)