# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Mouse_Events_in_OS_X.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Mouse_Events_in_OS_X.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mouse_Events_in_OS_X.dir/flags.make

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o: CMakeFiles/Mouse_Events_in_OS_X.dir/flags.make
CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o   -c /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/src/main.c

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/src/main.c > CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.i

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/src/main.c -o CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.s

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.requires

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.provides: CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/Mouse_Events_in_OS_X.dir/build.make CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.provides

CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.provides.build: CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o


# Object files for target Mouse_Events_in_OS_X
Mouse_Events_in_OS_X_OBJECTS = \
"CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o"

# External object files for target Mouse_Events_in_OS_X
Mouse_Events_in_OS_X_EXTERNAL_OBJECTS =

../outputs/bin/apple/mouse_events: CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o
../outputs/bin/apple/mouse_events: CMakeFiles/Mouse_Events_in_OS_X.dir/build.make
../outputs/bin/apple/mouse_events: ../outputs/lib/apple/libmouse_events.dylib
../outputs/bin/apple/mouse_events: CMakeFiles/Mouse_Events_in_OS_X.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../outputs/bin/apple/mouse_events"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mouse_Events_in_OS_X.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mouse_Events_in_OS_X.dir/build: ../outputs/bin/apple/mouse_events

.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/build

CMakeFiles/Mouse_Events_in_OS_X.dir/requires: CMakeFiles/Mouse_Events_in_OS_X.dir/src/main.c.o.requires

.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/requires

CMakeFiles/Mouse_Events_in_OS_X.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Mouse_Events_in_OS_X.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/clean

CMakeFiles/Mouse_Events_in_OS_X.dir/depend:
	cd /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/OS_X/mouse_events/cmake-build-debug/CMakeFiles/Mouse_Events_in_OS_X.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Mouse_Events_in_OS_X.dir/depend

