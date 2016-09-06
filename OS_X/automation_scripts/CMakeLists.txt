cmake_minimum_required(VERSION 3.5)
project(automation_scripts)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES automation_scripts.h automation_scripts.c system/windows.h system/windows.c)
# libraries paths
set(COCOA_HELPER_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/test/OS_X/cocoa_helper)

add_library(Automation_Scripts_Lib SHARED ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib PROPERTIES OUTPUT_NAME automation_scripts_shared)
target_link_libraries(Automation_Scripts_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib ${COCOA_HELPER_PATH}/libcocoa_helper.a)

add_library(Automation_Scripts_Lib_Static ${SOURCE_FILES})
set_target_properties(Automation_Scripts_Lib_Static PROPERTIES OUTPUT_NAME automation_scripts)
target_link_libraries(Automation_Scripts_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Automation_Scripts_Lib_Static ${COCOA_HELPER_PATH}/libcocoa_helper.a)

add_executable(Automation_Scripts_in_OS_X main.c)
target_link_libraries(Automation_Scripts_in_OS_X Automation_Scripts_Lib_Static)
# additional links are not needed if we are linking with static library:
#target_link_libraries(Automation_Scripts_in_OS_X ${APPLICATION_SERVICES_LIBRARY})
#target_link_libraries(Automation_Scripts_in_OS_X ${COCOA_HELPER_PATH}/libcocoa_helper.a)