# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/seonjo/Desktop/opengl/opengl_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/seonjo/Desktop/opengl/opengl_example/build

# Utility rule file for dep-spdlog.

# Include any custom commands dependencies for this target.
include CMakeFiles/dep-spdlog.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dep-spdlog.dir/progress.make

CMakeFiles/dep-spdlog: CMakeFiles/dep-spdlog-complete

CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-mkdir
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-build
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install
CMakeFiles/dep-spdlog-complete: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'dep-spdlog'"
	"C:/Program Files/CMake/bin/cmake.exe" -E make_directory C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles
	"C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles/dep-spdlog-complete
	"C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-done

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-build: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && $(MAKE)
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-build

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure: dep-spdlog-prefix/tmp/dep-spdlog-cfgcmd.txt
dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -DCMAKE_INSTALL_PREFIX=C:/Users/seonjo/Desktop/opengl/opengl_example/build/install "-GUnix Makefiles" -S C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog -B C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-gitinfo.txt
dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src && "C:/Program Files/CMake/bin/cmake.exe" -P C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/tmp/dep-spdlog-gitclone.cmake
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing install step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && $(MAKE) install
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'dep-spdlog'"
	"C:/Program Files/CMake/bin/cmake.exe" -Dcfgdir= -P C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/tmp/dep-spdlog-mkdirs.cmake
	"C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-mkdir

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch-info.txt
dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog && "C:/Program Files/CMake/bin/cmake.exe" -E echo_append
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-test: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -E echo_append
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-test

dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update-info.txt
dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No update step for 'dep-spdlog'"
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog && "C:/Program Files/CMake/bin/cmake.exe" -E echo_append
	cd C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog && "C:/Program Files/CMake/bin/cmake.exe" -E touch C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update

dep-spdlog: CMakeFiles/dep-spdlog
dep-spdlog: CMakeFiles/dep-spdlog-complete
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-build
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-configure
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-download
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-install
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-mkdir
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-patch
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-test
dep-spdlog: dep-spdlog-prefix/src/dep-spdlog-stamp/dep-spdlog-update
dep-spdlog: CMakeFiles/dep-spdlog.dir/build.make
.PHONY : dep-spdlog

# Rule to build all files generated by this target.
CMakeFiles/dep-spdlog.dir/build: dep-spdlog
.PHONY : CMakeFiles/dep-spdlog.dir/build

CMakeFiles/dep-spdlog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dep-spdlog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dep-spdlog.dir/clean

CMakeFiles/dep-spdlog.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/seonjo/Desktop/opengl/opengl_example C:/Users/seonjo/Desktop/opengl/opengl_example C:/Users/seonjo/Desktop/opengl/opengl_example/build C:/Users/seonjo/Desktop/opengl/opengl_example/build C:/Users/seonjo/Desktop/opengl/opengl_example/build/CMakeFiles/dep-spdlog.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/dep-spdlog.dir/depend

