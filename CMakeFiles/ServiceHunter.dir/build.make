# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/julian/Documents/GitHub/Service-Hunter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/julian/Documents/GitHub/Service-Hunter

# Include any dependencies generated for this target.
include CMakeFiles/ServiceHunter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ServiceHunter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ServiceHunter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServiceHunter.dir/flags.make

CMakeFiles/ServiceHunter.dir/src/main.cpp.o: CMakeFiles/ServiceHunter.dir/flags.make
CMakeFiles/ServiceHunter.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/ServiceHunter.dir/src/main.cpp.o: CMakeFiles/ServiceHunter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/julian/Documents/GitHub/Service-Hunter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ServiceHunter.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ServiceHunter.dir/src/main.cpp.o -MF CMakeFiles/ServiceHunter.dir/src/main.cpp.o.d -o CMakeFiles/ServiceHunter.dir/src/main.cpp.o -c /Users/julian/Documents/GitHub/Service-Hunter/src/main.cpp

CMakeFiles/ServiceHunter.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ServiceHunter.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/julian/Documents/GitHub/Service-Hunter/src/main.cpp > CMakeFiles/ServiceHunter.dir/src/main.cpp.i

CMakeFiles/ServiceHunter.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ServiceHunter.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/julian/Documents/GitHub/Service-Hunter/src/main.cpp -o CMakeFiles/ServiceHunter.dir/src/main.cpp.s

CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o: CMakeFiles/ServiceHunter.dir/flags.make
CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o: src/MainWindow.cpp
CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o: CMakeFiles/ServiceHunter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/julian/Documents/GitHub/Service-Hunter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o -MF CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o.d -o CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o -c /Users/julian/Documents/GitHub/Service-Hunter/src/MainWindow.cpp

CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/julian/Documents/GitHub/Service-Hunter/src/MainWindow.cpp > CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.i

CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/julian/Documents/GitHub/Service-Hunter/src/MainWindow.cpp -o CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.s

# Object files for target ServiceHunter
ServiceHunter_OBJECTS = \
"CMakeFiles/ServiceHunter.dir/src/main.cpp.o" \
"CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o"

# External object files for target ServiceHunter
ServiceHunter_EXTERNAL_OBJECTS =

ServiceHunter: CMakeFiles/ServiceHunter.dir/src/main.cpp.o
ServiceHunter: CMakeFiles/ServiceHunter.dir/src/MainWindow.cpp.o
ServiceHunter: CMakeFiles/ServiceHunter.dir/build.make
ServiceHunter: /Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics
ServiceHunter: /Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window
ServiceHunter: /Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
ServiceHunter: CMakeFiles/ServiceHunter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/julian/Documents/GitHub/Service-Hunter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ServiceHunter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServiceHunter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServiceHunter.dir/build: ServiceHunter
.PHONY : CMakeFiles/ServiceHunter.dir/build

CMakeFiles/ServiceHunter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ServiceHunter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ServiceHunter.dir/clean

CMakeFiles/ServiceHunter.dir/depend:
	cd /Users/julian/Documents/GitHub/Service-Hunter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/julian/Documents/GitHub/Service-Hunter /Users/julian/Documents/GitHub/Service-Hunter /Users/julian/Documents/GitHub/Service-Hunter /Users/julian/Documents/GitHub/Service-Hunter /Users/julian/Documents/GitHub/Service-Hunter/CMakeFiles/ServiceHunter.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ServiceHunter.dir/depend
