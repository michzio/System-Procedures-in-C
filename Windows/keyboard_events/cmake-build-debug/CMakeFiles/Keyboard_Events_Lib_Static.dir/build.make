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
CMAKE_SOURCE_DIR = /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Keyboard_Events_Lib_Static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Keyboard_Events_Lib_Static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Keyboard_Events_Lib_Static.dir/flags.make

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o: CMakeFiles/Keyboard_Events_Lib_Static.dir/flags.make
CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o: ../src/keyboard_events.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o   -c /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/keyboard_events.c

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/keyboard_events.c > CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.i

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/keyboard_events.c -o CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.s

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.requires:

.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.requires

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.provides: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.requires
	$(MAKE) -f CMakeFiles/Keyboard_Events_Lib_Static.dir/build.make CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.provides.build
.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.provides

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.provides.build: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o


CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o: CMakeFiles/Keyboard_Events_Lib_Static.dir/flags.make
CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o: ../src/hot_keys_events.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o   -c /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/hot_keys_events.c

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/hot_keys_events.c > CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.i

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/src/hot_keys_events.c -o CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.s

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.requires:

.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.requires

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.provides: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.requires
	$(MAKE) -f CMakeFiles/Keyboard_Events_Lib_Static.dir/build.make CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.provides.build
.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.provides

CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.provides.build: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o


# Object files for target Keyboard_Events_Lib_Static
Keyboard_Events_Lib_Static_OBJECTS = \
"CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o" \
"CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o"

# External object files for target Keyboard_Events_Lib_Static
Keyboard_Events_Lib_Static_EXTERNAL_OBJECTS =

../outputs/lib/cygwin/libkeyboard_events.a: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o
../outputs/lib/cygwin/libkeyboard_events.a: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o
../outputs/lib/cygwin/libkeyboard_events.a: CMakeFiles/Keyboard_Events_Lib_Static.dir/build.make
../outputs/lib/cygwin/libkeyboard_events.a: CMakeFiles/Keyboard_Events_Lib_Static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ../outputs/lib/cygwin/libkeyboard_events.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Keyboard_Events_Lib_Static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Keyboard_Events_Lib_Static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Keyboard_Events_Lib_Static.dir/build: ../outputs/lib/cygwin/libkeyboard_events.a

.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/build

CMakeFiles/Keyboard_Events_Lib_Static.dir/requires: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/keyboard_events.c.o.requires
CMakeFiles/Keyboard_Events_Lib_Static.dir/requires: CMakeFiles/Keyboard_Events_Lib_Static.dir/src/hot_keys_events.c.o.requires

.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/requires

CMakeFiles/Keyboard_Events_Lib_Static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Keyboard_Events_Lib_Static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/clean

CMakeFiles/Keyboard_Events_Lib_Static.dir/depend:
	cd /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug /Users/michzio/Developer/MyProjects/BachelorDegree/c/system/Windows/keyboard_events/cmake-build-debug/CMakeFiles/Keyboard_Events_Lib_Static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Keyboard_Events_Lib_Static.dir/depend

