# Install script for directory: /cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/windows_helpers.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin" TYPE EXECUTABLE FILES "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/cmake-build-debug/windows_helpers.exe")
  if(EXISTS "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/windows_helpers.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/windows_helpers.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip.exe" "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/windows_helpers.exe")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/lib/static/libwindows_helpers_shared.dll.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/lib/static" TYPE STATIC_LIBRARY OPTIONAL FILES "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/cmake-build-debug/libwindows_helpers_shared.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/cygwindows_helpers_shared.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin" TYPE SHARED_LIBRARY FILES "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/cmake-build-debug/cygwindows_helpers_shared.dll")
  if(EXISTS "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/cygwindows_helpers_shared.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/cygwindows_helpers_shared.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip.exe" "$ENV{DESTDIR}/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/bin/cygwindows_helpers_shared.dll")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/lib/static/libwindows_helpers.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/output/windows/lib/static" TYPE STATIC_LIBRARY FILES "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/cmake-build-debug/libwindows_helpers.a")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/cygdrive/c/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/windows_helpers/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
