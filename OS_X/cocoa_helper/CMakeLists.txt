cmake_minimum_required(VERSION 3.6)
project(Cocoa_Helper_in_OS_X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/cocoa_helper/strings.h src/cocoa_helper/strings.c include/cocoa_helper/property_list.h src/cocoa_helper/property_list.c include/cocoa_helper/exec_cmd.h src/cocoa_helper/exec_cmd.c include/cocoa_helper/images.h src/cocoa_helper/images.c include/cocoa_helper/file_system.h src/cocoa_helper/file_system.c)
set(TEST_SOURCE_FILES )

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
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)

# OpenCV libraries including
find_package( OpenCV REQUIRED core imgproc highgui)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

if(NOT DEFINED COMMON_FUNCTIONS_SRC_DIR)
# subprojects paths
set(COMMON_FUNCTIONS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../common)
set(COMMON_FUNCTIONS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../common/outputs)

# add subprojects
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${COMMON_FUNCTIONS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${COMMON_FUNCTIONS_BUILD_DIR} )
endif()

# include header files of subprojects
set(ZLIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib-1.2.8)
set(LIBPNG_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libpng-1.6.24)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/include)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/libraries)
include_directories(${ZLIB_SRC_DIR}/include)
include_directories(${LIBPNG_SRC_DIR}/include)

file(COPY tools DESTINATION .)
file(COPY tools DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# current project shared and static libraries creation
# SHARED
add_library(Cocoa_Helper_Lib SHARED ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Cocoa_Helper_Lib ${OpenCV_LIBS})
target_link_libraries(Cocoa_Helper_Lib Common_Functions_Lib)

# STATIC
add_library(Cocoa_Helper_Lib_Static ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib_Static PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Cocoa_Helper_Lib_Static ${OpenCV_LIBS})
target_link_libraries(Cocoa_Helper_Lib_Static Common_Functions_Lib_Static)

### MAKING EXECUTABLE ###
# current project executable creation
add_executable(Cocoa_Helper_in_OS_X src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Cocoa_Helper_in_OS_X PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_in_OS_X Cocoa_Helper_Lib)