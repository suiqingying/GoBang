# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/suiqingying/projects/GoBang

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/suiqingying/projects/GoBang/build

# Include any dependencies generated for this target.
include CMakeFiles/Gobang.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Gobang.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Gobang.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Gobang.dir/flags.make

CMakeFiles/Gobang.dir/draw.c.o: CMakeFiles/Gobang.dir/flags.make
CMakeFiles/Gobang.dir/draw.c.o: ../draw.c
CMakeFiles/Gobang.dir/draw.c.o: CMakeFiles/Gobang.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suiqingying/projects/GoBang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Gobang.dir/draw.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Gobang.dir/draw.c.o -MF CMakeFiles/Gobang.dir/draw.c.o.d -o CMakeFiles/Gobang.dir/draw.c.o -c /home/suiqingying/projects/GoBang/draw.c

CMakeFiles/Gobang.dir/draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Gobang.dir/draw.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/suiqingying/projects/GoBang/draw.c > CMakeFiles/Gobang.dir/draw.c.i

CMakeFiles/Gobang.dir/draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Gobang.dir/draw.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/suiqingying/projects/GoBang/draw.c -o CMakeFiles/Gobang.dir/draw.c.s

CMakeFiles/Gobang.dir/evaluation.c.o: CMakeFiles/Gobang.dir/flags.make
CMakeFiles/Gobang.dir/evaluation.c.o: ../evaluation.c
CMakeFiles/Gobang.dir/evaluation.c.o: CMakeFiles/Gobang.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suiqingying/projects/GoBang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Gobang.dir/evaluation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Gobang.dir/evaluation.c.o -MF CMakeFiles/Gobang.dir/evaluation.c.o.d -o CMakeFiles/Gobang.dir/evaluation.c.o -c /home/suiqingying/projects/GoBang/evaluation.c

CMakeFiles/Gobang.dir/evaluation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Gobang.dir/evaluation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/suiqingying/projects/GoBang/evaluation.c > CMakeFiles/Gobang.dir/evaluation.c.i

CMakeFiles/Gobang.dir/evaluation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Gobang.dir/evaluation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/suiqingying/projects/GoBang/evaluation.c -o CMakeFiles/Gobang.dir/evaluation.c.s

CMakeFiles/Gobang.dir/main.c.o: CMakeFiles/Gobang.dir/flags.make
CMakeFiles/Gobang.dir/main.c.o: ../main.c
CMakeFiles/Gobang.dir/main.c.o: CMakeFiles/Gobang.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suiqingying/projects/GoBang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Gobang.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Gobang.dir/main.c.o -MF CMakeFiles/Gobang.dir/main.c.o.d -o CMakeFiles/Gobang.dir/main.c.o -c /home/suiqingying/projects/GoBang/main.c

CMakeFiles/Gobang.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Gobang.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/suiqingying/projects/GoBang/main.c > CMakeFiles/Gobang.dir/main.c.i

CMakeFiles/Gobang.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Gobang.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/suiqingying/projects/GoBang/main.c -o CMakeFiles/Gobang.dir/main.c.s

CMakeFiles/Gobang.dir/search.c.o: CMakeFiles/Gobang.dir/flags.make
CMakeFiles/Gobang.dir/search.c.o: ../search.c
CMakeFiles/Gobang.dir/search.c.o: CMakeFiles/Gobang.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suiqingying/projects/GoBang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Gobang.dir/search.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Gobang.dir/search.c.o -MF CMakeFiles/Gobang.dir/search.c.o.d -o CMakeFiles/Gobang.dir/search.c.o -c /home/suiqingying/projects/GoBang/search.c

CMakeFiles/Gobang.dir/search.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Gobang.dir/search.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/suiqingying/projects/GoBang/search.c > CMakeFiles/Gobang.dir/search.c.i

CMakeFiles/Gobang.dir/search.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Gobang.dir/search.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/suiqingying/projects/GoBang/search.c -o CMakeFiles/Gobang.dir/search.c.s

# Object files for target Gobang
Gobang_OBJECTS = \
"CMakeFiles/Gobang.dir/draw.c.o" \
"CMakeFiles/Gobang.dir/evaluation.c.o" \
"CMakeFiles/Gobang.dir/main.c.o" \
"CMakeFiles/Gobang.dir/search.c.o"

# External object files for target Gobang
Gobang_EXTERNAL_OBJECTS =

Gobang: CMakeFiles/Gobang.dir/draw.c.o
Gobang: CMakeFiles/Gobang.dir/evaluation.c.o
Gobang: CMakeFiles/Gobang.dir/main.c.o
Gobang: CMakeFiles/Gobang.dir/search.c.o
Gobang: CMakeFiles/Gobang.dir/build.make
Gobang: CMakeFiles/Gobang.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/suiqingying/projects/GoBang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Gobang"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Gobang.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Gobang.dir/build: Gobang
.PHONY : CMakeFiles/Gobang.dir/build

CMakeFiles/Gobang.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Gobang.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Gobang.dir/clean

CMakeFiles/Gobang.dir/depend:
	cd /home/suiqingying/projects/GoBang/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/suiqingying/projects/GoBang /home/suiqingying/projects/GoBang /home/suiqingying/projects/GoBang/build /home/suiqingying/projects/GoBang/build /home/suiqingying/projects/GoBang/build/CMakeFiles/Gobang.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Gobang.dir/depend

