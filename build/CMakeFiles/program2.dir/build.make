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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build"

# Include any dependencies generated for this target.
include CMakeFiles/program2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/program2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/program2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program2.dir/flags.make

CMakeFiles/program2.dir/Program2.cpp.o: CMakeFiles/program2.dir/flags.make
CMakeFiles/program2.dir/Program2.cpp.o: /Users/josiahzacharias/Documents/School/UW\ Graduate/CSS\ 587/Program\ 2/Program2.cpp
CMakeFiles/program2.dir/Program2.cpp.o: CMakeFiles/program2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/program2.dir/Program2.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/program2.dir/Program2.cpp.o -MF CMakeFiles/program2.dir/Program2.cpp.o.d -o CMakeFiles/program2.dir/Program2.cpp.o -c "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/Program2.cpp"

CMakeFiles/program2.dir/Program2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/program2.dir/Program2.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/Program2.cpp" > CMakeFiles/program2.dir/Program2.cpp.i

CMakeFiles/program2.dir/Program2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/program2.dir/Program2.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/Program2.cpp" -o CMakeFiles/program2.dir/Program2.cpp.s

# Object files for target program2
program2_OBJECTS = \
"CMakeFiles/program2.dir/Program2.cpp.o"

# External object files for target program2
program2_EXTERNAL_OBJECTS =

program2: CMakeFiles/program2.dir/Program2.cpp.o
program2: CMakeFiles/program2.dir/build.make
program2: CMakeFiles/program2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable program2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/program2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program2.dir/build: program2
.PHONY : CMakeFiles/program2.dir/build

CMakeFiles/program2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/program2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/program2.dir/clean

CMakeFiles/program2.dir/depend:
	cd "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2" "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2" "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build" "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build" "/Users/josiahzacharias/Documents/School/UW Graduate/CSS 587/Program 2/build/CMakeFiles/program2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/program2.dir/depend

