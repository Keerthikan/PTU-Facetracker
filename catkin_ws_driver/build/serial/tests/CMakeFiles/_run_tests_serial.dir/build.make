# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kratnarajah/catkin_ws_PTU/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kratnarajah/catkin_ws_PTU/build

# Utility rule file for _run_tests_serial.

# Include the progress variables for this target.
include serial/tests/CMakeFiles/_run_tests_serial.dir/progress.make

serial/tests/CMakeFiles/_run_tests_serial:

_run_tests_serial: serial/tests/CMakeFiles/_run_tests_serial
_run_tests_serial: serial/tests/CMakeFiles/_run_tests_serial.dir/build.make
.PHONY : _run_tests_serial

# Rule to build all files generated by this target.
serial/tests/CMakeFiles/_run_tests_serial.dir/build: _run_tests_serial
.PHONY : serial/tests/CMakeFiles/_run_tests_serial.dir/build

serial/tests/CMakeFiles/_run_tests_serial.dir/clean:
	cd /home/kratnarajah/catkin_ws_PTU/build/serial/tests && $(CMAKE_COMMAND) -P CMakeFiles/_run_tests_serial.dir/cmake_clean.cmake
.PHONY : serial/tests/CMakeFiles/_run_tests_serial.dir/clean

serial/tests/CMakeFiles/_run_tests_serial.dir/depend:
	cd /home/kratnarajah/catkin_ws_PTU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kratnarajah/catkin_ws_PTU/src /home/kratnarajah/catkin_ws_PTU/src/serial/tests /home/kratnarajah/catkin_ws_PTU/build /home/kratnarajah/catkin_ws_PTU/build/serial/tests /home/kratnarajah/catkin_ws_PTU/build/serial/tests/CMakeFiles/_run_tests_serial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial/tests/CMakeFiles/_run_tests_serial.dir/depend

