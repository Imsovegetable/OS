# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\Chen Yining\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7717.62\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\Chen Yining\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7717.62\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Chen Yining\CLionProjects\OS"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/OS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS.dir/flags.make

CMakeFiles/OS.dir/os/main.cpp.obj: CMakeFiles/OS.dir/flags.make
CMakeFiles/OS.dir/os/main.cpp.obj: CMakeFiles/OS.dir/includes_CXX.rsp
CMakeFiles/OS.dir/os/main.cpp.obj: ../os/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OS.dir/os/main.cpp.obj"
	C:\Download\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\OS.dir\os\main.cpp.obj -c "C:\Users\Chen Yining\CLionProjects\OS\os\main.cpp"

CMakeFiles/OS.dir/os/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OS.dir/os/main.cpp.i"
	C:\Download\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Chen Yining\CLionProjects\OS\os\main.cpp" > CMakeFiles\OS.dir\os\main.cpp.i

CMakeFiles/OS.dir/os/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OS.dir/os/main.cpp.s"
	C:\Download\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Chen Yining\CLionProjects\OS\os\main.cpp" -o CMakeFiles\OS.dir\os\main.cpp.s

# Object files for target OS
OS_OBJECTS = \
"CMakeFiles/OS.dir/os/main.cpp.obj"

# External object files for target OS
OS_EXTERNAL_OBJECTS =

OS.exe: CMakeFiles/OS.dir/os/main.cpp.obj
OS.exe: CMakeFiles/OS.dir/build.make
OS.exe: CMakeFiles/OS.dir/linklibs.rsp
OS.exe: CMakeFiles/OS.dir/objects1.rsp
OS.exe: CMakeFiles/OS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OS.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OS.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS.dir/build: OS.exe

.PHONY : CMakeFiles/OS.dir/build

CMakeFiles/OS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OS.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OS.dir/clean

CMakeFiles/OS.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Chen Yining\CLionProjects\OS" "C:\Users\Chen Yining\CLionProjects\OS" "C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug" "C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug" "C:\Users\Chen Yining\CLionProjects\OS\cmake-build-debug\CMakeFiles\OS.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/OS.dir/depend
