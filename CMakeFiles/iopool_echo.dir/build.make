# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = "/home/router/Documents/muduo_example/timing wheel"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/router/Documents/muduo_example/timing wheel"

# Include any dependencies generated for this target.
include CMakeFiles/iopool_echo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iopool_echo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iopool_echo.dir/flags.make

CMakeFiles/iopool_echo.dir/iopool_echo.cc.o: CMakeFiles/iopool_echo.dir/flags.make
CMakeFiles/iopool_echo.dir/iopool_echo.cc.o: iopool_echo.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/router/Documents/muduo_example/timing wheel/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/iopool_echo.dir/iopool_echo.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/iopool_echo.dir/iopool_echo.cc.o -c "/home/router/Documents/muduo_example/timing wheel/iopool_echo.cc"

CMakeFiles/iopool_echo.dir/iopool_echo.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/iopool_echo.dir/iopool_echo.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/router/Documents/muduo_example/timing wheel/iopool_echo.cc" > CMakeFiles/iopool_echo.dir/iopool_echo.cc.i

CMakeFiles/iopool_echo.dir/iopool_echo.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/iopool_echo.dir/iopool_echo.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/router/Documents/muduo_example/timing wheel/iopool_echo.cc" -o CMakeFiles/iopool_echo.dir/iopool_echo.cc.s

CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.requires:

.PHONY : CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.requires

CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.provides: CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.requires
	$(MAKE) -f CMakeFiles/iopool_echo.dir/build.make CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.provides.build
.PHONY : CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.provides

CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.provides.build: CMakeFiles/iopool_echo.dir/iopool_echo.cc.o


# Object files for target iopool_echo
iopool_echo_OBJECTS = \
"CMakeFiles/iopool_echo.dir/iopool_echo.cc.o"

# External object files for target iopool_echo
iopool_echo_EXTERNAL_OBJECTS =

bin/iopool_echo: CMakeFiles/iopool_echo.dir/iopool_echo.cc.o
bin/iopool_echo: CMakeFiles/iopool_echo.dir/build.make
bin/iopool_echo: CMakeFiles/iopool_echo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/router/Documents/muduo_example/timing wheel/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/iopool_echo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iopool_echo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iopool_echo.dir/build: bin/iopool_echo

.PHONY : CMakeFiles/iopool_echo.dir/build

CMakeFiles/iopool_echo.dir/requires: CMakeFiles/iopool_echo.dir/iopool_echo.cc.o.requires

.PHONY : CMakeFiles/iopool_echo.dir/requires

CMakeFiles/iopool_echo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iopool_echo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iopool_echo.dir/clean

CMakeFiles/iopool_echo.dir/depend:
	cd "/home/router/Documents/muduo_example/timing wheel" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/router/Documents/muduo_example/timing wheel" "/home/router/Documents/muduo_example/timing wheel" "/home/router/Documents/muduo_example/timing wheel" "/home/router/Documents/muduo_example/timing wheel" "/home/router/Documents/muduo_example/timing wheel/CMakeFiles/iopool_echo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/iopool_echo.dir/depend

