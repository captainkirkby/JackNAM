# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/patch/Developer/jack_nam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patch/Developer/jack_nam/build

# Include any dependencies generated for this target.
include CMakeFiles/jack_nam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jack_nam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jack_nam.dir/flags.make

CMakeFiles/jack_nam.dir/src/main.cpp.o: CMakeFiles/jack_nam.dir/flags.make
CMakeFiles/jack_nam.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patch/Developer/jack_nam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jack_nam.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jack_nam.dir/src/main.cpp.o -c /home/patch/Developer/jack_nam/src/main.cpp

CMakeFiles/jack_nam.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jack_nam.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patch/Developer/jack_nam/src/main.cpp > CMakeFiles/jack_nam.dir/src/main.cpp.i

CMakeFiles/jack_nam.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jack_nam.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patch/Developer/jack_nam/src/main.cpp -o CMakeFiles/jack_nam.dir/src/main.cpp.s

# Object files for target jack_nam
jack_nam_OBJECTS = \
"CMakeFiles/jack_nam.dir/src/main.cpp.o"

# External object files for target jack_nam
jack_nam_EXTERNAL_OBJECTS =

jack_nam: CMakeFiles/jack_nam.dir/src/main.cpp.o
jack_nam: CMakeFiles/jack_nam.dir/build.make
jack_nam: libneural_amp_modeler.a
jack_nam: CMakeFiles/jack_nam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/patch/Developer/jack_nam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jack_nam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jack_nam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jack_nam.dir/build: jack_nam

.PHONY : CMakeFiles/jack_nam.dir/build

CMakeFiles/jack_nam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jack_nam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jack_nam.dir/clean

CMakeFiles/jack_nam.dir/depend:
	cd /home/patch/Developer/jack_nam/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patch/Developer/jack_nam /home/patch/Developer/jack_nam /home/patch/Developer/jack_nam/build /home/patch/Developer/jack_nam/build /home/patch/Developer/jack_nam/build/CMakeFiles/jack_nam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jack_nam.dir/depend
