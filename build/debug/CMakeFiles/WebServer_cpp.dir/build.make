# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.mVpPkaiCIB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.mVpPkaiCIB/build/debug

# Include any dependencies generated for this target.
include CMakeFiles/WebServer_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/WebServer_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer_cpp.dir/flags.make

CMakeFiles/WebServer_cpp.dir/src/main.cpp.o: CMakeFiles/WebServer_cpp.dir/flags.make
CMakeFiles/WebServer_cpp.dir/src/main.cpp.o: /tmp/tmp.mVpPkaiCIB/src/main.cpp
CMakeFiles/WebServer_cpp.dir/src/main.cpp.o: CMakeFiles/WebServer_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.mVpPkaiCIB/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WebServer_cpp.dir/src/main.cpp.o"
	/usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer_cpp.dir/src/main.cpp.o -MF CMakeFiles/WebServer_cpp.dir/src/main.cpp.o.d -o CMakeFiles/WebServer_cpp.dir/src/main.cpp.o -c /tmp/tmp.mVpPkaiCIB/src/main.cpp

CMakeFiles/WebServer_cpp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer_cpp.dir/src/main.cpp.i"
	/usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.mVpPkaiCIB/src/main.cpp > CMakeFiles/WebServer_cpp.dir/src/main.cpp.i

CMakeFiles/WebServer_cpp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer_cpp.dir/src/main.cpp.s"
	/usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.mVpPkaiCIB/src/main.cpp -o CMakeFiles/WebServer_cpp.dir/src/main.cpp.s

# Object files for target WebServer_cpp
WebServer_cpp_OBJECTS = \
"CMakeFiles/WebServer_cpp.dir/src/main.cpp.o"

# External object files for target WebServer_cpp
WebServer_cpp_EXTERNAL_OBJECTS =

WebServer_cpp: CMakeFiles/WebServer_cpp.dir/src/main.cpp.o
WebServer_cpp: CMakeFiles/WebServer_cpp.dir/build.make
WebServer_cpp: CMakeFiles/WebServer_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.mVpPkaiCIB/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WebServer_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer_cpp.dir/build: WebServer_cpp
.PHONY : CMakeFiles/WebServer_cpp.dir/build

CMakeFiles/WebServer_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer_cpp.dir/clean

CMakeFiles/WebServer_cpp.dir/depend:
	cd /tmp/tmp.mVpPkaiCIB/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.mVpPkaiCIB /tmp/tmp.mVpPkaiCIB /tmp/tmp.mVpPkaiCIB/build/debug /tmp/tmp.mVpPkaiCIB/build/debug /tmp/tmp.mVpPkaiCIB/build/debug/CMakeFiles/WebServer_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer_cpp.dir/depend

