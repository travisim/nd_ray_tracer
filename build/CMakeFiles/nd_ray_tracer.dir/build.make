# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/k/Downloads/cody/nd_ray_tracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/k/Downloads/cody/nd_ray_tracer/build

# Include any dependencies generated for this target.
include CMakeFiles/nd_ray_tracer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nd_ray_tracer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nd_ray_tracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nd_ray_tracer.dir/flags.make

CMakeFiles/nd_ray_tracer.dir/codegen:
.PHONY : CMakeFiles/nd_ray_tracer.dir/codegen

CMakeFiles/nd_ray_tracer.dir/main.cpp.o: CMakeFiles/nd_ray_tracer.dir/flags.make
CMakeFiles/nd_ray_tracer.dir/main.cpp.o: /Users/k/Downloads/cody/nd_ray_tracer/main.cpp
CMakeFiles/nd_ray_tracer.dir/main.cpp.o: CMakeFiles/nd_ray_tracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/k/Downloads/cody/nd_ray_tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nd_ray_tracer.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nd_ray_tracer.dir/main.cpp.o -MF CMakeFiles/nd_ray_tracer.dir/main.cpp.o.d -o CMakeFiles/nd_ray_tracer.dir/main.cpp.o -c /Users/k/Downloads/cody/nd_ray_tracer/main.cpp

CMakeFiles/nd_ray_tracer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nd_ray_tracer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/k/Downloads/cody/nd_ray_tracer/main.cpp > CMakeFiles/nd_ray_tracer.dir/main.cpp.i

CMakeFiles/nd_ray_tracer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nd_ray_tracer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/k/Downloads/cody/nd_ray_tracer/main.cpp -o CMakeFiles/nd_ray_tracer.dir/main.cpp.s

CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o: CMakeFiles/nd_ray_tracer.dir/flags.make
CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o: /Users/k/Downloads/cody/nd_ray_tracer/nd_ray_tracer.cpp
CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o: CMakeFiles/nd_ray_tracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/k/Downloads/cody/nd_ray_tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o -MF CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o.d -o CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o -c /Users/k/Downloads/cody/nd_ray_tracer/nd_ray_tracer.cpp

CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/k/Downloads/cody/nd_ray_tracer/nd_ray_tracer.cpp > CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.i

CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/k/Downloads/cody/nd_ray_tracer/nd_ray_tracer.cpp -o CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.s

CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o: CMakeFiles/nd_ray_tracer.dir/flags.make
CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o: /Users/k/Downloads/cody/nd_ray_tracer/plotting.cpp
CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o: CMakeFiles/nd_ray_tracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/k/Downloads/cody/nd_ray_tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o -MF CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o.d -o CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o -c /Users/k/Downloads/cody/nd_ray_tracer/plotting.cpp

CMakeFiles/nd_ray_tracer.dir/plotting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nd_ray_tracer.dir/plotting.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/k/Downloads/cody/nd_ray_tracer/plotting.cpp > CMakeFiles/nd_ray_tracer.dir/plotting.cpp.i

CMakeFiles/nd_ray_tracer.dir/plotting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nd_ray_tracer.dir/plotting.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/k/Downloads/cody/nd_ray_tracer/plotting.cpp -o CMakeFiles/nd_ray_tracer.dir/plotting.cpp.s

# Object files for target nd_ray_tracer
nd_ray_tracer_OBJECTS = \
"CMakeFiles/nd_ray_tracer.dir/main.cpp.o" \
"CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o" \
"CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o"

# External object files for target nd_ray_tracer
nd_ray_tracer_EXTERNAL_OBJECTS =

nd_ray_tracer: CMakeFiles/nd_ray_tracer.dir/main.cpp.o
nd_ray_tracer: CMakeFiles/nd_ray_tracer.dir/nd_ray_tracer.cpp.o
nd_ray_tracer: CMakeFiles/nd_ray_tracer.dir/plotting.cpp.o
nd_ray_tracer: CMakeFiles/nd_ray_tracer.dir/build.make
nd_ray_tracer: CMakeFiles/nd_ray_tracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/k/Downloads/cody/nd_ray_tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable nd_ray_tracer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nd_ray_tracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nd_ray_tracer.dir/build: nd_ray_tracer
.PHONY : CMakeFiles/nd_ray_tracer.dir/build

CMakeFiles/nd_ray_tracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nd_ray_tracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nd_ray_tracer.dir/clean

CMakeFiles/nd_ray_tracer.dir/depend:
	cd /Users/k/Downloads/cody/nd_ray_tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/k/Downloads/cody/nd_ray_tracer /Users/k/Downloads/cody/nd_ray_tracer /Users/k/Downloads/cody/nd_ray_tracer/build /Users/k/Downloads/cody/nd_ray_tracer/build /Users/k/Downloads/cody/nd_ray_tracer/build/CMakeFiles/nd_ray_tracer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/nd_ray_tracer.dir/depend

