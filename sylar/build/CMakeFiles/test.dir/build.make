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
CMAKE_SOURCE_DIR = /pgdata/projetcs/cJSON/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /pgdata/projetcs/cJSON/sylar/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/sylar/muti.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/sylar/muti.cpp.o: ../sylar/muti.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /pgdata/projetcs/cJSON/sylar/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/sylar/muti.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/sylar/muti.cpp.o -c /pgdata/projetcs/cJSON/sylar/sylar/muti.cpp

CMakeFiles/test.dir/sylar/muti.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/sylar/muti.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /pgdata/projetcs/cJSON/sylar/sylar/muti.cpp > CMakeFiles/test.dir/sylar/muti.cpp.i

CMakeFiles/test.dir/sylar/muti.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/sylar/muti.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /pgdata/projetcs/cJSON/sylar/sylar/muti.cpp -o CMakeFiles/test.dir/sylar/muti.cpp.s

CMakeFiles/test.dir/sylar/muti.cpp.o.requires:
.PHONY : CMakeFiles/test.dir/sylar/muti.cpp.o.requires

CMakeFiles/test.dir/sylar/muti.cpp.o.provides: CMakeFiles/test.dir/sylar/muti.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/sylar/muti.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/sylar/muti.cpp.o.provides

CMakeFiles/test.dir/sylar/muti.cpp.o.provides.build: CMakeFiles/test.dir/sylar/muti.cpp.o

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/sylar/muti.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/sylar/muti.cpp.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/requires: CMakeFiles/test.dir/sylar/muti.cpp.o.requires
.PHONY : CMakeFiles/test.dir/requires

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /pgdata/projetcs/cJSON/sylar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /pgdata/projetcs/cJSON/sylar /pgdata/projetcs/cJSON/sylar /pgdata/projetcs/cJSON/sylar/build /pgdata/projetcs/cJSON/sylar/build /pgdata/projetcs/cJSON/sylar/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

