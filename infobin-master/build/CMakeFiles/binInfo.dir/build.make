# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /pgdata/projetcs/cJSON/infobin-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /pgdata/projetcs/cJSON/infobin-master/build

# Include any dependencies generated for this target.
include CMakeFiles/binInfo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/binInfo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/binInfo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/binInfo.dir/flags.make

CMakeFiles/binInfo.dir/binlogInfo/log.c.o: CMakeFiles/binInfo.dir/flags.make
CMakeFiles/binInfo.dir/binlogInfo/log.c.o: /pgdata/projetcs/cJSON/infobin-master/binlogInfo/log.c
CMakeFiles/binInfo.dir/binlogInfo/log.c.o: CMakeFiles/binInfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/pgdata/projetcs/cJSON/infobin-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/binInfo.dir/binlogInfo/log.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/binInfo.dir/binlogInfo/log.c.o -MF CMakeFiles/binInfo.dir/binlogInfo/log.c.o.d -o CMakeFiles/binInfo.dir/binlogInfo/log.c.o -c /pgdata/projetcs/cJSON/infobin-master/binlogInfo/log.c

CMakeFiles/binInfo.dir/binlogInfo/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/binInfo.dir/binlogInfo/log.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /pgdata/projetcs/cJSON/infobin-master/binlogInfo/log.c > CMakeFiles/binInfo.dir/binlogInfo/log.c.i

CMakeFiles/binInfo.dir/binlogInfo/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/binInfo.dir/binlogInfo/log.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /pgdata/projetcs/cJSON/infobin-master/binlogInfo/log.c -o CMakeFiles/binInfo.dir/binlogInfo/log.c.s

CMakeFiles/binInfo.dir/binlogInfo/main.c.o: CMakeFiles/binInfo.dir/flags.make
CMakeFiles/binInfo.dir/binlogInfo/main.c.o: /pgdata/projetcs/cJSON/infobin-master/binlogInfo/main.c
CMakeFiles/binInfo.dir/binlogInfo/main.c.o: CMakeFiles/binInfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/pgdata/projetcs/cJSON/infobin-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/binInfo.dir/binlogInfo/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/binInfo.dir/binlogInfo/main.c.o -MF CMakeFiles/binInfo.dir/binlogInfo/main.c.o.d -o CMakeFiles/binInfo.dir/binlogInfo/main.c.o -c /pgdata/projetcs/cJSON/infobin-master/binlogInfo/main.c

CMakeFiles/binInfo.dir/binlogInfo/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/binInfo.dir/binlogInfo/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /pgdata/projetcs/cJSON/infobin-master/binlogInfo/main.c > CMakeFiles/binInfo.dir/binlogInfo/main.c.i

CMakeFiles/binInfo.dir/binlogInfo/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/binInfo.dir/binlogInfo/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /pgdata/projetcs/cJSON/infobin-master/binlogInfo/main.c -o CMakeFiles/binInfo.dir/binlogInfo/main.c.s

CMakeFiles/binInfo.dir/binlogInfo/total.c.o: CMakeFiles/binInfo.dir/flags.make
CMakeFiles/binInfo.dir/binlogInfo/total.c.o: /pgdata/projetcs/cJSON/infobin-master/binlogInfo/total.c
CMakeFiles/binInfo.dir/binlogInfo/total.c.o: CMakeFiles/binInfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/pgdata/projetcs/cJSON/infobin-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/binInfo.dir/binlogInfo/total.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/binInfo.dir/binlogInfo/total.c.o -MF CMakeFiles/binInfo.dir/binlogInfo/total.c.o.d -o CMakeFiles/binInfo.dir/binlogInfo/total.c.o -c /pgdata/projetcs/cJSON/infobin-master/binlogInfo/total.c

CMakeFiles/binInfo.dir/binlogInfo/total.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/binInfo.dir/binlogInfo/total.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /pgdata/projetcs/cJSON/infobin-master/binlogInfo/total.c > CMakeFiles/binInfo.dir/binlogInfo/total.c.i

CMakeFiles/binInfo.dir/binlogInfo/total.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/binInfo.dir/binlogInfo/total.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /pgdata/projetcs/cJSON/infobin-master/binlogInfo/total.c -o CMakeFiles/binInfo.dir/binlogInfo/total.c.s

# Object files for target binInfo
binInfo_OBJECTS = \
"CMakeFiles/binInfo.dir/binlogInfo/log.c.o" \
"CMakeFiles/binInfo.dir/binlogInfo/main.c.o" \
"CMakeFiles/binInfo.dir/binlogInfo/total.c.o"

# External object files for target binInfo
binInfo_EXTERNAL_OBJECTS =

/pgdata/projetcs/cJSON/infobin-master/bin/binInfo: CMakeFiles/binInfo.dir/binlogInfo/log.c.o
/pgdata/projetcs/cJSON/infobin-master/bin/binInfo: CMakeFiles/binInfo.dir/binlogInfo/main.c.o
/pgdata/projetcs/cJSON/infobin-master/bin/binInfo: CMakeFiles/binInfo.dir/binlogInfo/total.c.o
/pgdata/projetcs/cJSON/infobin-master/bin/binInfo: CMakeFiles/binInfo.dir/build.make
/pgdata/projetcs/cJSON/infobin-master/bin/binInfo: CMakeFiles/binInfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/pgdata/projetcs/cJSON/infobin-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable /pgdata/projetcs/cJSON/infobin-master/bin/binInfo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binInfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/binInfo.dir/build: /pgdata/projetcs/cJSON/infobin-master/bin/binInfo
.PHONY : CMakeFiles/binInfo.dir/build

CMakeFiles/binInfo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/binInfo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/binInfo.dir/clean

CMakeFiles/binInfo.dir/depend:
	cd /pgdata/projetcs/cJSON/infobin-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /pgdata/projetcs/cJSON/infobin-master /pgdata/projetcs/cJSON/infobin-master /pgdata/projetcs/cJSON/infobin-master/build /pgdata/projetcs/cJSON/infobin-master/build /pgdata/projetcs/cJSON/infobin-master/build/CMakeFiles/binInfo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/binInfo.dir/depend
