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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator"

# Include any dependencies generated for this target.
include CMakeFiles/RISC-V_Simulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RISC-V_Simulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RISC-V_Simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RISC-V_Simulator.dir/flags.make

CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o: CMakeFiles/RISC-V_Simulator.dir/flags.make
CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o: src\ copy/genUtils.cpp
CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o: CMakeFiles/RISC-V_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o -MF CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o.d -o CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o -c "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/genUtils.cpp"

CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/genUtils.cpp" > CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.i

CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/genUtils.cpp" -o CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.s

CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o: CMakeFiles/RISC-V_Simulator.dir/flags.make
CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o: src\ copy/memory.cpp
CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o: CMakeFiles/RISC-V_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o -MF CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o.d -o CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o -c "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/memory.cpp"

CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/memory.cpp" > CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.i

CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/memory.cpp" -o CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.s

CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o: CMakeFiles/RISC-V_Simulator.dir/flags.make
CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o: src\ copy/test.cpp
CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o: CMakeFiles/RISC-V_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o -MF CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o.d -o CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o -c "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/test.cpp"

CMakeFiles/RISC-V_Simulator.dir/src_copy/test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RISC-V_Simulator.dir/src_copy/test.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/test.cpp" > CMakeFiles/RISC-V_Simulator.dir/src_copy/test.i

CMakeFiles/RISC-V_Simulator.dir/src_copy/test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RISC-V_Simulator.dir/src_copy/test.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/src copy/test.cpp" -o CMakeFiles/RISC-V_Simulator.dir/src_copy/test.s

# Object files for target RISC-V_Simulator
RISC__V_Simulator_OBJECTS = \
"CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o" \
"CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o" \
"CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o"

# External object files for target RISC-V_Simulator
RISC__V_Simulator_EXTERNAL_OBJECTS =

RISC-V_Simulator: CMakeFiles/RISC-V_Simulator.dir/src_copy/genUtils.o
RISC-V_Simulator: CMakeFiles/RISC-V_Simulator.dir/src_copy/memory.o
RISC-V_Simulator: CMakeFiles/RISC-V_Simulator.dir/src_copy/test.o
RISC-V_Simulator: CMakeFiles/RISC-V_Simulator.dir/build.make
RISC-V_Simulator: CMakeFiles/RISC-V_Simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable RISC-V_Simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RISC-V_Simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RISC-V_Simulator.dir/build: RISC-V_Simulator
.PHONY : CMakeFiles/RISC-V_Simulator.dir/build

CMakeFiles/RISC-V_Simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RISC-V_Simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RISC-V_Simulator.dir/clean

CMakeFiles/RISC-V_Simulator.dir/depend:
	cd "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator" "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator" "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator" "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator" "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/CMakeFiles/RISC-V_Simulator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/RISC-V_Simulator.dir/depend

