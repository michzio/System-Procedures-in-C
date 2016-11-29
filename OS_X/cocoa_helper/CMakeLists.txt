cmake_minimum_required(VERSION 3.6)
project(Cocoa_Helper_in_OS_X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES strings.h strings.c property_list.h property_list.c exec_cmd.h exec_cmd.c images.h images.c file_system.h file_system.c)
set(TEST_SOURCE_FILES )

# OpenCV library including
find_package( OpenCV REQUIRED core imgproc highgui)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# OS X Cocoa libraries including
find_library(APPLICATION_SERVICES_LIBRARY ApplicationServices)
mark_as_advanced(APPLICATION_SERVICES_LIBRARY)

# libraries paths
set(COMMON_FUNCTIONS_PATH ${CMAKE_SOURCE_DIR}/../../../common)
set(LIBPNG_PATH ${CMAKE_SOURCE_DIR}/../../../libpng-1.6.24)
set(ZLIB_PATH ${CMAKE_SOURCE_DIR}/../../../zlib-1.2.8)

set(COMMON_FUNCTIONS_LIB_PATH ${COMMON_FUNCTIONS_PATH}/output/unix/lib/static/libcommon_functions.a)
set(LIBPNG_LIB_PATH ${LIBPNG_PATH}/output/unix/lib/static/liblibpng.a)
set(ZLIB_LIB_PATH ${ZLIB_PATH}/output/unix/lib/static/libzlib.a)

file(COPY tools DESTINATION .)

add_library(Cocoa_Helper_Lib SHARED ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib PROPERTIES OUTPUT_NAME cocoa_helper_shared)
target_link_libraries(Cocoa_Helper_Lib ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Cocoa_Helper_Lib ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib ${LIBPNG_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib ${ZLIB_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib ${OpenCV_LIBS})

add_library(Cocoa_Helper_Lib_Static ${SOURCE_FILES})
set_target_properties(Cocoa_Helper_Lib_Static PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_Lib_Static ${APPLICATION_SERVICES_LIBRARY})
target_link_libraries(Cocoa_Helper_Lib_Static ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib_Static ${LIBPNG_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib_Static ${ZLIB_LIB_PATH})
target_link_libraries(Cocoa_Helper_Lib_Static ${OpenCV_LIBS})

add_executable(Cocoa_Helper_in_OS_X main.c ${TEST_SOURCE_FILES})
set_target_properties(Cocoa_Helper_in_OS_X PROPERTIES OUTPUT_NAME cocoa_helper)
target_link_libraries(Cocoa_Helper_in_OS_X Cocoa_Helper_Lib_Static)

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

# apple
set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/bin)
set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib)
set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/apple/lib/static)

install(TARGETS Cocoa_Helper_in_OS_X Cocoa_Helper_Lib Cocoa_Helper_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})