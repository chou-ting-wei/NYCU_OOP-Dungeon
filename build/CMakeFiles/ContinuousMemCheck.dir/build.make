# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.29.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.29.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon/build

# Utility rule file for ContinuousMemCheck.

# Include any custom commands dependencies for this target.
include CMakeFiles/ContinuousMemCheck.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ContinuousMemCheck.dir/progress.make

CMakeFiles/ContinuousMemCheck:
	/usr/local/Cellar/cmake/3.29.0/bin/ctest -D ContinuousMemCheck

ContinuousMemCheck: CMakeFiles/ContinuousMemCheck
ContinuousMemCheck: CMakeFiles/ContinuousMemCheck.dir/build.make
.PHONY : ContinuousMemCheck

# Rule to build all files generated by this target.
CMakeFiles/ContinuousMemCheck.dir/build: ContinuousMemCheck
.PHONY : CMakeFiles/ContinuousMemCheck.dir/build

CMakeFiles/ContinuousMemCheck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ContinuousMemCheck.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ContinuousMemCheck.dir/clean

CMakeFiles/ContinuousMemCheck.dir/depend:
	cd /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon/build /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon/build /Users/chou.ting.wei/Coding/NYCU/OOP/dungeon/build/CMakeFiles/ContinuousMemCheck.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ContinuousMemCheck.dir/depend

