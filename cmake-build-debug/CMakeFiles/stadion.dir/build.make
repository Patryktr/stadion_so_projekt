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
CMAKE_COMMAND = /snap/clion/314/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/314/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/patryk/CLionProjects/stadion_so_projekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/stadion.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stadion.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stadion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stadion.dir/flags.make

CMakeFiles/stadion.dir/main.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/main.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/main.cpp
CMakeFiles/stadion.dir/main.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stadion.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/main.cpp.o -MF CMakeFiles/stadion.dir/main.cpp.o.d -o CMakeFiles/stadion.dir/main.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/main.cpp

CMakeFiles/stadion.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/main.cpp > CMakeFiles/stadion.dir/main.cpp.i

CMakeFiles/stadion.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/main.cpp -o CMakeFiles/stadion.dir/main.cpp.s

CMakeFiles/stadion.dir/Stadion.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/Stadion.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/Stadion.cpp
CMakeFiles/stadion.dir/Stadion.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stadion.dir/Stadion.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/Stadion.cpp.o -MF CMakeFiles/stadion.dir/Stadion.cpp.o.d -o CMakeFiles/stadion.dir/Stadion.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/Stadion.cpp

CMakeFiles/stadion.dir/Stadion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/Stadion.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/Stadion.cpp > CMakeFiles/stadion.dir/Stadion.cpp.i

CMakeFiles/stadion.dir/Stadion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/Stadion.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/Stadion.cpp -o CMakeFiles/stadion.dir/Stadion.cpp.s

CMakeFiles/stadion.dir/Fan.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/Fan.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/Fan.cpp
CMakeFiles/stadion.dir/Fan.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/stadion.dir/Fan.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/Fan.cpp.o -MF CMakeFiles/stadion.dir/Fan.cpp.o.d -o CMakeFiles/stadion.dir/Fan.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/Fan.cpp

CMakeFiles/stadion.dir/Fan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/Fan.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/Fan.cpp > CMakeFiles/stadion.dir/Fan.cpp.i

CMakeFiles/stadion.dir/Fan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/Fan.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/Fan.cpp -o CMakeFiles/stadion.dir/Fan.cpp.s

CMakeFiles/stadion.dir/Pracownik_tech.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/Pracownik_tech.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/Pracownik_tech.cpp
CMakeFiles/stadion.dir/Pracownik_tech.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/stadion.dir/Pracownik_tech.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/Pracownik_tech.cpp.o -MF CMakeFiles/stadion.dir/Pracownik_tech.cpp.o.d -o CMakeFiles/stadion.dir/Pracownik_tech.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/Pracownik_tech.cpp

CMakeFiles/stadion.dir/Pracownik_tech.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/Pracownik_tech.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/Pracownik_tech.cpp > CMakeFiles/stadion.dir/Pracownik_tech.cpp.i

CMakeFiles/stadion.dir/Pracownik_tech.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/Pracownik_tech.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/Pracownik_tech.cpp -o CMakeFiles/stadion.dir/Pracownik_tech.cpp.s

CMakeFiles/stadion.dir/Gate.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/Gate.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/Gate.cpp
CMakeFiles/stadion.dir/Gate.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/stadion.dir/Gate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/Gate.cpp.o -MF CMakeFiles/stadion.dir/Gate.cpp.o.d -o CMakeFiles/stadion.dir/Gate.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/Gate.cpp

CMakeFiles/stadion.dir/Gate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/Gate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/Gate.cpp > CMakeFiles/stadion.dir/Gate.cpp.i

CMakeFiles/stadion.dir/Gate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/Gate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/Gate.cpp -o CMakeFiles/stadion.dir/Gate.cpp.s

CMakeFiles/stadion.dir/Kierownik.cpp.o: CMakeFiles/stadion.dir/flags.make
CMakeFiles/stadion.dir/Kierownik.cpp.o: /home/patryk/CLionProjects/stadion_so_projekt/Kierownik.cpp
CMakeFiles/stadion.dir/Kierownik.cpp.o: CMakeFiles/stadion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/stadion.dir/Kierownik.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stadion.dir/Kierownik.cpp.o -MF CMakeFiles/stadion.dir/Kierownik.cpp.o.d -o CMakeFiles/stadion.dir/Kierownik.cpp.o -c /home/patryk/CLionProjects/stadion_so_projekt/Kierownik.cpp

CMakeFiles/stadion.dir/Kierownik.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stadion.dir/Kierownik.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patryk/CLionProjects/stadion_so_projekt/Kierownik.cpp > CMakeFiles/stadion.dir/Kierownik.cpp.i

CMakeFiles/stadion.dir/Kierownik.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stadion.dir/Kierownik.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patryk/CLionProjects/stadion_so_projekt/Kierownik.cpp -o CMakeFiles/stadion.dir/Kierownik.cpp.s

# Object files for target stadion
stadion_OBJECTS = \
"CMakeFiles/stadion.dir/main.cpp.o" \
"CMakeFiles/stadion.dir/Stadion.cpp.o" \
"CMakeFiles/stadion.dir/Fan.cpp.o" \
"CMakeFiles/stadion.dir/Pracownik_tech.cpp.o" \
"CMakeFiles/stadion.dir/Gate.cpp.o" \
"CMakeFiles/stadion.dir/Kierownik.cpp.o"

# External object files for target stadion
stadion_EXTERNAL_OBJECTS =

stadion: CMakeFiles/stadion.dir/main.cpp.o
stadion: CMakeFiles/stadion.dir/Stadion.cpp.o
stadion: CMakeFiles/stadion.dir/Fan.cpp.o
stadion: CMakeFiles/stadion.dir/Pracownik_tech.cpp.o
stadion: CMakeFiles/stadion.dir/Gate.cpp.o
stadion: CMakeFiles/stadion.dir/Kierownik.cpp.o
stadion: CMakeFiles/stadion.dir/build.make
stadion: CMakeFiles/stadion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable stadion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stadion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stadion.dir/build: stadion
.PHONY : CMakeFiles/stadion.dir/build

CMakeFiles/stadion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stadion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stadion.dir/clean

CMakeFiles/stadion.dir/depend:
	cd /home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patryk/CLionProjects/stadion_so_projekt /home/patryk/CLionProjects/stadion_so_projekt /home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug /home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug /home/patryk/CLionProjects/stadion_so_projekt/cmake-build-debug/CMakeFiles/stadion.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/stadion.dir/depend

