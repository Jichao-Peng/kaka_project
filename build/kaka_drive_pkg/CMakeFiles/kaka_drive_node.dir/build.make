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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leo/Desktop/Kaka_Project/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leo/Desktop/Kaka_Project/build

# Include any dependencies generated for this target.
include kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/depend.make

# Include the progress variables for this target.
include kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/progress.make

# Include the compile flags for this target's objects.
include kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/flags.make

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/flags.make
kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o: /home/leo/Desktop/Kaka_Project/src/kaka_drive_pkg/src/KakaDrive.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/leo/Desktop/Kaka_Project/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o"
	cd /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o -c /home/leo/Desktop/Kaka_Project/src/kaka_drive_pkg/src/KakaDrive.cpp

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.i"
	cd /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/leo/Desktop/Kaka_Project/src/kaka_drive_pkg/src/KakaDrive.cpp > CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.i

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.s"
	cd /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/leo/Desktop/Kaka_Project/src/kaka_drive_pkg/src/KakaDrive.cpp -o CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.s

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.requires:
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.requires

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.provides: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.requires
	$(MAKE) -f kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/build.make kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.provides.build
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.provides

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.provides.build: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o

# Object files for target kaka_drive_node
kaka_drive_node_OBJECTS = \
"CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o"

# External object files for target kaka_drive_node
kaka_drive_node_EXTERNAL_OBJECTS =

/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/build.make
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libtf.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libtf2_ros.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libactionlib.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libmessage_filters.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libroscpp.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libtf2.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/librosconsole.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/liblog4cxx.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/librostime.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /opt/ros/indigo/lib/libcpp_common.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node"
	cd /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kaka_drive_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/build: /home/leo/Desktop/Kaka_Project/devel/lib/kaka_drive_pkg/kaka_drive_node
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/build

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/requires: kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/src/KakaDrive.cpp.o.requires
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/requires

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/clean:
	cd /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg && $(CMAKE_COMMAND) -P CMakeFiles/kaka_drive_node.dir/cmake_clean.cmake
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/clean

kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/depend:
	cd /home/leo/Desktop/Kaka_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leo/Desktop/Kaka_Project/src /home/leo/Desktop/Kaka_Project/src/kaka_drive_pkg /home/leo/Desktop/Kaka_Project/build /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg /home/leo/Desktop/Kaka_Project/build/kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kaka_drive_pkg/CMakeFiles/kaka_drive_node.dir/depend

