# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/duyx/CLionProjects/Reversi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/duyx/CLionProjects/Reversi/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Reversi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Reversi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Reversi.dir/flags.make

CMakeFiles/Reversi.dir/main.cpp.o: CMakeFiles/Reversi.dir/flags.make
CMakeFiles/Reversi.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Reversi.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Reversi.dir/main.cpp.o -c /Users/duyx/CLionProjects/Reversi/main.cpp

CMakeFiles/Reversi.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Reversi.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/duyx/CLionProjects/Reversi/main.cpp > CMakeFiles/Reversi.dir/main.cpp.i

CMakeFiles/Reversi.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Reversi.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/duyx/CLionProjects/Reversi/main.cpp -o CMakeFiles/Reversi.dir/main.cpp.s

CMakeFiles/Reversi.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Reversi.dir/main.cpp.o.requires

CMakeFiles/Reversi.dir/main.cpp.o.provides: CMakeFiles/Reversi.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Reversi.dir/build.make CMakeFiles/Reversi.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Reversi.dir/main.cpp.o.provides

CMakeFiles/Reversi.dir/main.cpp.o.provides.build: CMakeFiles/Reversi.dir/main.cpp.o


CMakeFiles/Reversi.dir/Board.cpp.o: CMakeFiles/Reversi.dir/flags.make
CMakeFiles/Reversi.dir/Board.cpp.o: ../Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Reversi.dir/Board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Reversi.dir/Board.cpp.o -c /Users/duyx/CLionProjects/Reversi/Board.cpp

CMakeFiles/Reversi.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Reversi.dir/Board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/duyx/CLionProjects/Reversi/Board.cpp > CMakeFiles/Reversi.dir/Board.cpp.i

CMakeFiles/Reversi.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Reversi.dir/Board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/duyx/CLionProjects/Reversi/Board.cpp -o CMakeFiles/Reversi.dir/Board.cpp.s

CMakeFiles/Reversi.dir/Board.cpp.o.requires:

.PHONY : CMakeFiles/Reversi.dir/Board.cpp.o.requires

CMakeFiles/Reversi.dir/Board.cpp.o.provides: CMakeFiles/Reversi.dir/Board.cpp.o.requires
	$(MAKE) -f CMakeFiles/Reversi.dir/build.make CMakeFiles/Reversi.dir/Board.cpp.o.provides.build
.PHONY : CMakeFiles/Reversi.dir/Board.cpp.o.provides

CMakeFiles/Reversi.dir/Board.cpp.o.provides.build: CMakeFiles/Reversi.dir/Board.cpp.o


CMakeFiles/Reversi.dir/Reversi.cpp.o: CMakeFiles/Reversi.dir/flags.make
CMakeFiles/Reversi.dir/Reversi.cpp.o: ../Reversi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Reversi.dir/Reversi.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Reversi.dir/Reversi.cpp.o -c /Users/duyx/CLionProjects/Reversi/Reversi.cpp

CMakeFiles/Reversi.dir/Reversi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Reversi.dir/Reversi.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/duyx/CLionProjects/Reversi/Reversi.cpp > CMakeFiles/Reversi.dir/Reversi.cpp.i

CMakeFiles/Reversi.dir/Reversi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Reversi.dir/Reversi.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/duyx/CLionProjects/Reversi/Reversi.cpp -o CMakeFiles/Reversi.dir/Reversi.cpp.s

CMakeFiles/Reversi.dir/Reversi.cpp.o.requires:

.PHONY : CMakeFiles/Reversi.dir/Reversi.cpp.o.requires

CMakeFiles/Reversi.dir/Reversi.cpp.o.provides: CMakeFiles/Reversi.dir/Reversi.cpp.o.requires
	$(MAKE) -f CMakeFiles/Reversi.dir/build.make CMakeFiles/Reversi.dir/Reversi.cpp.o.provides.build
.PHONY : CMakeFiles/Reversi.dir/Reversi.cpp.o.provides

CMakeFiles/Reversi.dir/Reversi.cpp.o.provides.build: CMakeFiles/Reversi.dir/Reversi.cpp.o


CMakeFiles/Reversi.dir/ClientSocket.cpp.o: CMakeFiles/Reversi.dir/flags.make
CMakeFiles/Reversi.dir/ClientSocket.cpp.o: ../ClientSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Reversi.dir/ClientSocket.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Reversi.dir/ClientSocket.cpp.o -c /Users/duyx/CLionProjects/Reversi/ClientSocket.cpp

CMakeFiles/Reversi.dir/ClientSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Reversi.dir/ClientSocket.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/duyx/CLionProjects/Reversi/ClientSocket.cpp > CMakeFiles/Reversi.dir/ClientSocket.cpp.i

CMakeFiles/Reversi.dir/ClientSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Reversi.dir/ClientSocket.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/duyx/CLionProjects/Reversi/ClientSocket.cpp -o CMakeFiles/Reversi.dir/ClientSocket.cpp.s

CMakeFiles/Reversi.dir/ClientSocket.cpp.o.requires:

.PHONY : CMakeFiles/Reversi.dir/ClientSocket.cpp.o.requires

CMakeFiles/Reversi.dir/ClientSocket.cpp.o.provides: CMakeFiles/Reversi.dir/ClientSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/Reversi.dir/build.make CMakeFiles/Reversi.dir/ClientSocket.cpp.o.provides.build
.PHONY : CMakeFiles/Reversi.dir/ClientSocket.cpp.o.provides

CMakeFiles/Reversi.dir/ClientSocket.cpp.o.provides.build: CMakeFiles/Reversi.dir/ClientSocket.cpp.o


# Object files for target Reversi
Reversi_OBJECTS = \
"CMakeFiles/Reversi.dir/main.cpp.o" \
"CMakeFiles/Reversi.dir/Board.cpp.o" \
"CMakeFiles/Reversi.dir/Reversi.cpp.o" \
"CMakeFiles/Reversi.dir/ClientSocket.cpp.o"

# External object files for target Reversi
Reversi_EXTERNAL_OBJECTS =

Reversi: CMakeFiles/Reversi.dir/main.cpp.o
Reversi: CMakeFiles/Reversi.dir/Board.cpp.o
Reversi: CMakeFiles/Reversi.dir/Reversi.cpp.o
Reversi: CMakeFiles/Reversi.dir/ClientSocket.cpp.o
Reversi: CMakeFiles/Reversi.dir/build.make
Reversi: CMakeFiles/Reversi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Reversi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Reversi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Reversi.dir/build: Reversi

.PHONY : CMakeFiles/Reversi.dir/build

CMakeFiles/Reversi.dir/requires: CMakeFiles/Reversi.dir/main.cpp.o.requires
CMakeFiles/Reversi.dir/requires: CMakeFiles/Reversi.dir/Board.cpp.o.requires
CMakeFiles/Reversi.dir/requires: CMakeFiles/Reversi.dir/Reversi.cpp.o.requires
CMakeFiles/Reversi.dir/requires: CMakeFiles/Reversi.dir/ClientSocket.cpp.o.requires

.PHONY : CMakeFiles/Reversi.dir/requires

CMakeFiles/Reversi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Reversi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Reversi.dir/clean

CMakeFiles/Reversi.dir/depend:
	cd /Users/duyx/CLionProjects/Reversi/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/duyx/CLionProjects/Reversi /Users/duyx/CLionProjects/Reversi /Users/duyx/CLionProjects/Reversi/cmake-build-debug /Users/duyx/CLionProjects/Reversi/cmake-build-debug /Users/duyx/CLionProjects/Reversi/cmake-build-debug/CMakeFiles/Reversi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Reversi.dir/depend
