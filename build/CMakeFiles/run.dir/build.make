# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/duskel/Documents/Github/textures_data

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/duskel/Documents/Github/textures_data/build

# Include any dependencies generated for this target.
include CMakeFiles/run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/run.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run.dir/flags.make

CMakeFiles/run.dir/main.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/main.cpp.o: /home/duskel/Documents/Github/textures_data/main.cpp
CMakeFiles/run.dir/main.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/duskel/Documents/Github/textures_data/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/main.cpp.o -MF CMakeFiles/run.dir/main.cpp.o.d -o CMakeFiles/run.dir/main.cpp.o -c /home/duskel/Documents/Github/textures_data/main.cpp

CMakeFiles/run.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duskel/Documents/Github/textures_data/main.cpp > CMakeFiles/run.dir/main.cpp.i

CMakeFiles/run.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duskel/Documents/Github/textures_data/main.cpp -o CMakeFiles/run.dir/main.cpp.s

CMakeFiles/run.dir/EfrosLeung.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/EfrosLeung.cpp.o: /home/duskel/Documents/Github/textures_data/EfrosLeung.cpp
CMakeFiles/run.dir/EfrosLeung.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/duskel/Documents/Github/textures_data/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run.dir/EfrosLeung.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/EfrosLeung.cpp.o -MF CMakeFiles/run.dir/EfrosLeung.cpp.o.d -o CMakeFiles/run.dir/EfrosLeung.cpp.o -c /home/duskel/Documents/Github/textures_data/EfrosLeung.cpp

CMakeFiles/run.dir/EfrosLeung.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/EfrosLeung.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duskel/Documents/Github/textures_data/EfrosLeung.cpp > CMakeFiles/run.dir/EfrosLeung.cpp.i

CMakeFiles/run.dir/EfrosLeung.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/EfrosLeung.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duskel/Documents/Github/textures_data/EfrosLeung.cpp -o CMakeFiles/run.dir/EfrosLeung.cpp.s

# Object files for target run
run_OBJECTS = \
"CMakeFiles/run.dir/main.cpp.o" \
"CMakeFiles/run.dir/EfrosLeung.cpp.o"

# External object files for target run
run_EXTERNAL_OBJECTS =

run: CMakeFiles/run.dir/main.cpp.o
run: CMakeFiles/run.dir/EfrosLeung.cpp.o
run: CMakeFiles/run.dir/build.make
run: /usr/lib/libopencv_gapi.so.4.8.0
run: /usr/lib/libopencv_stitching.so.4.8.0
run: /usr/lib/libopencv_alphamat.so.4.8.0
run: /usr/lib/libopencv_aruco.so.4.8.0
run: /usr/lib/libopencv_bgsegm.so.4.8.0
run: /usr/lib/libopencv_bioinspired.so.4.8.0
run: /usr/lib/libopencv_ccalib.so.4.8.0
run: /usr/lib/libopencv_cvv.so.4.8.0
run: /usr/lib/libopencv_dnn_objdetect.so.4.8.0
run: /usr/lib/libopencv_dnn_superres.so.4.8.0
run: /usr/lib/libopencv_dpm.so.4.8.0
run: /usr/lib/libopencv_face.so.4.8.0
run: /usr/lib/libopencv_freetype.so.4.8.0
run: /usr/lib/libopencv_fuzzy.so.4.8.0
run: /usr/lib/libopencv_hdf.so.4.8.0
run: /usr/lib/libopencv_hfs.so.4.8.0
run: /usr/lib/libopencv_img_hash.so.4.8.0
run: /usr/lib/libopencv_intensity_transform.so.4.8.0
run: /usr/lib/libopencv_line_descriptor.so.4.8.0
run: /usr/lib/libopencv_mcc.so.4.8.0
run: /usr/lib/libopencv_quality.so.4.8.0
run: /usr/lib/libopencv_rapid.so.4.8.0
run: /usr/lib/libopencv_reg.so.4.8.0
run: /usr/lib/libopencv_rgbd.so.4.8.0
run: /usr/lib/libopencv_saliency.so.4.8.0
run: /usr/lib/libopencv_stereo.so.4.8.0
run: /usr/lib/libopencv_structured_light.so.4.8.0
run: /usr/lib/libopencv_superres.so.4.8.0
run: /usr/lib/libopencv_surface_matching.so.4.8.0
run: /usr/lib/libopencv_tracking.so.4.8.0
run: /usr/lib/libopencv_videostab.so.4.8.0
run: /usr/lib/libopencv_viz.so.4.8.0
run: /usr/lib/libopencv_wechat_qrcode.so.4.8.0
run: /usr/lib/libopencv_xfeatures2d.so.4.8.0
run: /usr/lib/libopencv_xobjdetect.so.4.8.0
run: /usr/lib/libopencv_xphoto.so.4.8.0
run: /usr/lib/libopencv_shape.so.4.8.0
run: /usr/lib/libopencv_highgui.so.4.8.0
run: /usr/lib/libopencv_datasets.so.4.8.0
run: /usr/lib/libopencv_plot.so.4.8.0
run: /usr/lib/libopencv_text.so.4.8.0
run: /usr/lib/libopencv_ml.so.4.8.0
run: /usr/lib/libopencv_phase_unwrapping.so.4.8.0
run: /usr/lib/libopencv_optflow.so.4.8.0
run: /usr/lib/libopencv_ximgproc.so.4.8.0
run: /usr/lib/libopencv_video.so.4.8.0
run: /usr/lib/libopencv_videoio.so.4.8.0
run: /usr/lib/libopencv_imgcodecs.so.4.8.0
run: /usr/lib/libopencv_objdetect.so.4.8.0
run: /usr/lib/libopencv_calib3d.so.4.8.0
run: /usr/lib/libopencv_dnn.so.4.8.0
run: /usr/lib/libopencv_features2d.so.4.8.0
run: /usr/lib/libopencv_flann.so.4.8.0
run: /usr/lib/libopencv_photo.so.4.8.0
run: /usr/lib/libopencv_imgproc.so.4.8.0
run: /usr/lib/libopencv_core.so.4.8.0
run: CMakeFiles/run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/duskel/Documents/Github/textures_data/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run.dir/build: run
.PHONY : CMakeFiles/run.dir/build

CMakeFiles/run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run.dir/clean

CMakeFiles/run.dir/depend:
	cd /home/duskel/Documents/Github/textures_data/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/duskel/Documents/Github/textures_data /home/duskel/Documents/Github/textures_data /home/duskel/Documents/Github/textures_data/build /home/duskel/Documents/Github/textures_data/build /home/duskel/Documents/Github/textures_data/build/CMakeFiles/run.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/run.dir/depend
