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
CMAKE_SOURCE_DIR = /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns

# Include any dependencies generated for this target.
include CMakeFiles/testeOCV.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testeOCV.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testeOCV.dir/flags.make

CMakeFiles/testeOCV.dir/testeOCV.cpp.o: CMakeFiles/testeOCV.dir/flags.make
CMakeFiles/testeOCV.dir/testeOCV.cpp.o: testeOCV.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testeOCV.dir/testeOCV.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testeOCV.dir/testeOCV.cpp.o -c /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/testeOCV.cpp

CMakeFiles/testeOCV.dir/testeOCV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testeOCV.dir/testeOCV.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/testeOCV.cpp > CMakeFiles/testeOCV.dir/testeOCV.cpp.i

CMakeFiles/testeOCV.dir/testeOCV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testeOCV.dir/testeOCV.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/testeOCV.cpp -o CMakeFiles/testeOCV.dir/testeOCV.cpp.s

CMakeFiles/testeOCV.dir/testeOCV.cpp.o.requires:

.PHONY : CMakeFiles/testeOCV.dir/testeOCV.cpp.o.requires

CMakeFiles/testeOCV.dir/testeOCV.cpp.o.provides: CMakeFiles/testeOCV.dir/testeOCV.cpp.o.requires
	$(MAKE) -f CMakeFiles/testeOCV.dir/build.make CMakeFiles/testeOCV.dir/testeOCV.cpp.o.provides.build
.PHONY : CMakeFiles/testeOCV.dir/testeOCV.cpp.o.provides

CMakeFiles/testeOCV.dir/testeOCV.cpp.o.provides.build: CMakeFiles/testeOCV.dir/testeOCV.cpp.o


# Object files for target testeOCV
testeOCV_OBJECTS = \
"CMakeFiles/testeOCV.dir/testeOCV.cpp.o"

# External object files for target testeOCV
testeOCV_EXTERNAL_OBJECTS =

testeOCV: CMakeFiles/testeOCV.dir/testeOCV.cpp.o
testeOCV: CMakeFiles/testeOCV.dir/build.make
testeOCV: /usr/local/lib/libopencv_videostab.so.2.4.10
testeOCV: /usr/local/lib/libopencv_ts.a
testeOCV: /usr/local/lib/libopencv_superres.so.2.4.10
testeOCV: /usr/local/lib/libopencv_stitching.so.2.4.10
testeOCV: /usr/local/lib/libopencv_contrib.so.2.4.10
testeOCV: /usr/lib/x86_64-linux-gnu/libGLU.so
testeOCV: /usr/lib/x86_64-linux-gnu/libGL.so
testeOCV: /usr/local/lib/libopencv_nonfree.so.2.4.10
testeOCV: /usr/local/lib/libopencv_ocl.so.2.4.10
testeOCV: /usr/local/lib/libopencv_gpu.so.2.4.10
testeOCV: /usr/local/lib/libopencv_photo.so.2.4.10
testeOCV: /usr/local/lib/libopencv_objdetect.so.2.4.10
testeOCV: /usr/local/lib/libopencv_legacy.so.2.4.10
testeOCV: /usr/local/lib/libopencv_video.so.2.4.10
testeOCV: /usr/local/lib/libopencv_ml.so.2.4.10
testeOCV: /usr/local/lib/libopencv_calib3d.so.2.4.10
testeOCV: /usr/local/lib/libopencv_features2d.so.2.4.10
testeOCV: /usr/local/lib/libopencv_highgui.so.2.4.10
testeOCV: /usr/local/lib/libopencv_imgproc.so.2.4.10
testeOCV: /usr/local/lib/libopencv_flann.so.2.4.10
testeOCV: /usr/local/lib/libopencv_core.so.2.4.10
testeOCV: CMakeFiles/testeOCV.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testeOCV"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testeOCV.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testeOCV.dir/build: testeOCV

.PHONY : CMakeFiles/testeOCV.dir/build

CMakeFiles/testeOCV.dir/requires: CMakeFiles/testeOCV.dir/testeOCV.cpp.o.requires

.PHONY : CMakeFiles/testeOCV.dir/requires

CMakeFiles/testeOCV.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testeOCV.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testeOCV.dir/clean

CMakeFiles/testeOCV.dir/depend:
	cd /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns /home/frankamente/repositorios/github/TFG/Trabajo/OCVSigns/CMakeFiles/testeOCV.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testeOCV.dir/depend

