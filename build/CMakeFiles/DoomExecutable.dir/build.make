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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pingan/recreation-of-doom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pingan/recreation-of-doom/build

# Include any dependencies generated for this target.
include CMakeFiles/DoomExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DoomExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DoomExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DoomExecutable.dir/flags.make

CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o: CMakeFiles/DoomExecutable.dir/flags.make
CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o: /Users/pingan/recreation-of-doom/src/glfw_tutorial.c
CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o: CMakeFiles/DoomExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/pingan/recreation-of-doom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o -MF CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o.d -o CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o -c /Users/pingan/recreation-of-doom/src/glfw_tutorial.c

CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pingan/recreation-of-doom/src/glfw_tutorial.c > CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.i

CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pingan/recreation-of-doom/src/glfw_tutorial.c -o CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.s

CMakeFiles/DoomExecutable.dir/src/glad.c.o: CMakeFiles/DoomExecutable.dir/flags.make
CMakeFiles/DoomExecutable.dir/src/glad.c.o: /Users/pingan/recreation-of-doom/src/glad.c
CMakeFiles/DoomExecutable.dir/src/glad.c.o: CMakeFiles/DoomExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/pingan/recreation-of-doom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/DoomExecutable.dir/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DoomExecutable.dir/src/glad.c.o -MF CMakeFiles/DoomExecutable.dir/src/glad.c.o.d -o CMakeFiles/DoomExecutable.dir/src/glad.c.o -c /Users/pingan/recreation-of-doom/src/glad.c

CMakeFiles/DoomExecutable.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DoomExecutable.dir/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pingan/recreation-of-doom/src/glad.c > CMakeFiles/DoomExecutable.dir/src/glad.c.i

CMakeFiles/DoomExecutable.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DoomExecutable.dir/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pingan/recreation-of-doom/src/glad.c -o CMakeFiles/DoomExecutable.dir/src/glad.c.s

# Object files for target DoomExecutable
DoomExecutable_OBJECTS = \
"CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o" \
"CMakeFiles/DoomExecutable.dir/src/glad.c.o"

# External object files for target DoomExecutable
DoomExecutable_EXTERNAL_OBJECTS =

DoomExecutable: CMakeFiles/DoomExecutable.dir/src/glfw_tutorial.c.o
DoomExecutable: CMakeFiles/DoomExecutable.dir/src/glad.c.o
DoomExecutable: CMakeFiles/DoomExecutable.dir/build.make
DoomExecutable: /opt/homebrew/lib/libglfw.3.4.dylib
DoomExecutable: CMakeFiles/DoomExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/pingan/recreation-of-doom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable DoomExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DoomExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DoomExecutable.dir/build: DoomExecutable
.PHONY : CMakeFiles/DoomExecutable.dir/build

CMakeFiles/DoomExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DoomExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DoomExecutable.dir/clean

CMakeFiles/DoomExecutable.dir/depend:
	cd /Users/pingan/recreation-of-doom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pingan/recreation-of-doom /Users/pingan/recreation-of-doom /Users/pingan/recreation-of-doom/build /Users/pingan/recreation-of-doom/build /Users/pingan/recreation-of-doom/build/CMakeFiles/DoomExecutable.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DoomExecutable.dir/depend
