# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /snap/cmake/1299/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1299/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexander_gaponov/CLionProjects/CAOS_server_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexander_gaponov/CLionProjects/CAOS_server_project/build

# Include any dependencies generated for this target.
include CMakeFiles/client_caos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client_caos.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client_caos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_caos.dir/flags.make

CMakeFiles/client_caos.dir/client.c.o: CMakeFiles/client_caos.dir/flags.make
CMakeFiles/client_caos.dir/client.c.o: /home/alexander_gaponov/CLionProjects/CAOS_server_project/client.c
CMakeFiles/client_caos.dir/client.c.o: CMakeFiles/client_caos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander_gaponov/CLionProjects/CAOS_server_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client_caos.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client_caos.dir/client.c.o -MF CMakeFiles/client_caos.dir/client.c.o.d -o CMakeFiles/client_caos.dir/client.c.o -c /home/alexander_gaponov/CLionProjects/CAOS_server_project/client.c

CMakeFiles/client_caos.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_caos.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alexander_gaponov/CLionProjects/CAOS_server_project/client.c > CMakeFiles/client_caos.dir/client.c.i

CMakeFiles/client_caos.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_caos.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alexander_gaponov/CLionProjects/CAOS_server_project/client.c -o CMakeFiles/client_caos.dir/client.c.s

# Object files for target client_caos
client_caos_OBJECTS = \
"CMakeFiles/client_caos.dir/client.c.o"

# External object files for target client_caos
client_caos_EXTERNAL_OBJECTS =

client_caos: CMakeFiles/client_caos.dir/client.c.o
client_caos: CMakeFiles/client_caos.dir/build.make
client_caos: CMakeFiles/client_caos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexander_gaponov/CLionProjects/CAOS_server_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable client_caos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_caos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_caos.dir/build: client_caos
.PHONY : CMakeFiles/client_caos.dir/build

CMakeFiles/client_caos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_caos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_caos.dir/clean

CMakeFiles/client_caos.dir/depend:
	cd /home/alexander_gaponov/CLionProjects/CAOS_server_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexander_gaponov/CLionProjects/CAOS_server_project /home/alexander_gaponov/CLionProjects/CAOS_server_project /home/alexander_gaponov/CLionProjects/CAOS_server_project/build /home/alexander_gaponov/CLionProjects/CAOS_server_project/build /home/alexander_gaponov/CLionProjects/CAOS_server_project/build/CMakeFiles/client_caos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_caos.dir/depend

