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
CMAKE_SOURCE_DIR = /home/kratnarajah/own/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kratnarajah/own/build

# Include any dependencies generated for this target.
include cam/CMakeFiles/hello.dir/depend.make

# Include the progress variables for this target.
include cam/CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include cam/CMakeFiles/hello.dir/flags.make

cam/CMakeFiles/hello.dir/hello.cpp.o: cam/CMakeFiles/hello.dir/flags.make
cam/CMakeFiles/hello.dir/hello.cpp.o: /home/kratnarajah/own/src/cam/hello.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kratnarajah/own/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object cam/CMakeFiles/hello.dir/hello.cpp.o"
	cd /home/kratnarajah/own/build/cam && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hello.dir/hello.cpp.o -c /home/kratnarajah/own/src/cam/hello.cpp

cam/CMakeFiles/hello.dir/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hello.dir/hello.cpp.i"
	cd /home/kratnarajah/own/build/cam && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kratnarajah/own/src/cam/hello.cpp > CMakeFiles/hello.dir/hello.cpp.i

cam/CMakeFiles/hello.dir/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hello.dir/hello.cpp.s"
	cd /home/kratnarajah/own/build/cam && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kratnarajah/own/src/cam/hello.cpp -o CMakeFiles/hello.dir/hello.cpp.s

cam/CMakeFiles/hello.dir/hello.cpp.o.requires:
.PHONY : cam/CMakeFiles/hello.dir/hello.cpp.o.requires

cam/CMakeFiles/hello.dir/hello.cpp.o.provides: cam/CMakeFiles/hello.dir/hello.cpp.o.requires
	$(MAKE) -f cam/CMakeFiles/hello.dir/build.make cam/CMakeFiles/hello.dir/hello.cpp.o.provides.build
.PHONY : cam/CMakeFiles/hello.dir/hello.cpp.o.provides

cam/CMakeFiles/hello.dir/hello.cpp.o.provides.build: cam/CMakeFiles/hello.dir/hello.cpp.o

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/hello.cpp.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

/home/kratnarajah/own/devel/lib/cam/hello: cam/CMakeFiles/hello.dir/hello.cpp.o
/home/kratnarajah/own/devel/lib/cam/hello: cam/CMakeFiles/hello.dir/build.make
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/libroscpp.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/librosconsole.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/liblog4cxx.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/librostime.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/kratnarajah/own/devel/lib/cam/hello: /opt/ros/indigo/lib/libcpp_common.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/kratnarajah/own/devel/lib/cam/hello: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/kratnarajah/own/devel/lib/cam/hello: cam/CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/kratnarajah/own/devel/lib/cam/hello"
	cd /home/kratnarajah/own/build/cam && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cam/CMakeFiles/hello.dir/build: /home/kratnarajah/own/devel/lib/cam/hello
.PHONY : cam/CMakeFiles/hello.dir/build

cam/CMakeFiles/hello.dir/requires: cam/CMakeFiles/hello.dir/hello.cpp.o.requires
.PHONY : cam/CMakeFiles/hello.dir/requires

cam/CMakeFiles/hello.dir/clean:
	cd /home/kratnarajah/own/build/cam && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : cam/CMakeFiles/hello.dir/clean

cam/CMakeFiles/hello.dir/depend:
	cd /home/kratnarajah/own/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kratnarajah/own/src /home/kratnarajah/own/src/cam /home/kratnarajah/own/build /home/kratnarajah/own/build/cam /home/kratnarajah/own/build/cam/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cam/CMakeFiles/hello.dir/depend
