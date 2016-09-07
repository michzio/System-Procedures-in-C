cmake_minimum_required(VERSION 3.5)
project(Cocoa_Helper_in_OS_X)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES strings.h strings.c property_list.h property_list.c)

add_library(Cocoa_Helper_Lib SHARED ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib PROPERTIES OUTPUT_NAME cocoa_helper_shared)
target_link_libraries(Cocoa_Helper_Lib ${APPLICATION_SERVICES_LIBRARY})

add_library(Cocoa_Helper_Lib_Static ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib_Static PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_Lib_Static ${APPLICATION_SERVICES_LIBRARY})

add_executable(Cocoa_Helper_in_OS_X main.c)
target_link_libraries(Cocoa_Helper_in_OS_X Cocoa_Helper_Lib_Static)