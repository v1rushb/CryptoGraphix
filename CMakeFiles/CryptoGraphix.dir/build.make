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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/v1rushb/newDev/newCopyCryptanalysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/v1rushb/newDev/newCopyCryptanalysis

# Include any dependencies generated for this target.
include CMakeFiles/CryptoGraphix.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CryptoGraphix.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CryptoGraphix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CryptoGraphix.dir/flags.make

CMakeFiles/CryptoGraphix.dir/src/main.cpp.o: CMakeFiles/CryptoGraphix.dir/flags.make
CMakeFiles/CryptoGraphix.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/CryptoGraphix.dir/src/main.cpp.o: CMakeFiles/CryptoGraphix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CryptoGraphix.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CryptoGraphix.dir/src/main.cpp.o -MF CMakeFiles/CryptoGraphix.dir/src/main.cpp.o.d -o CMakeFiles/CryptoGraphix.dir/src/main.cpp.o -c /home/v1rushb/newDev/newCopyCryptanalysis/src/main.cpp

CMakeFiles/CryptoGraphix.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CryptoGraphix.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/v1rushb/newDev/newCopyCryptanalysis/src/main.cpp > CMakeFiles/CryptoGraphix.dir/src/main.cpp.i

CMakeFiles/CryptoGraphix.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CryptoGraphix.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/v1rushb/newDev/newCopyCryptanalysis/src/main.cpp -o CMakeFiles/CryptoGraphix.dir/src/main.cpp.s

CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o: CMakeFiles/CryptoGraphix.dir/flags.make
CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o: src/ImageReader.cpp
CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o: CMakeFiles/CryptoGraphix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o -MF CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o.d -o CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o -c /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageReader.cpp

CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageReader.cpp > CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.i

CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageReader.cpp -o CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.s

CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o: CMakeFiles/CryptoGraphix.dir/flags.make
CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o: src/ImageWriter.cpp
CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o: CMakeFiles/CryptoGraphix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o -MF CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o.d -o CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o -c /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageWriter.cpp

CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageWriter.cpp > CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.i

CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/v1rushb/newDev/newCopyCryptanalysis/src/ImageWriter.cpp -o CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.s

CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o: CMakeFiles/CryptoGraphix.dir/flags.make
CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o: src/AES256Encryption.cpp
CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o: CMakeFiles/CryptoGraphix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o -MF CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o.d -o CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o -c /home/v1rushb/newDev/newCopyCryptanalysis/src/AES256Encryption.cpp

CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/v1rushb/newDev/newCopyCryptanalysis/src/AES256Encryption.cpp > CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.i

CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/v1rushb/newDev/newCopyCryptanalysis/src/AES256Encryption.cpp -o CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.s

CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o: CMakeFiles/CryptoGraphix.dir/flags.make
CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o: src/IEncrypt.cpp
CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o: CMakeFiles/CryptoGraphix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o -MF CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o.d -o CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o -c /home/v1rushb/newDev/newCopyCryptanalysis/src/IEncrypt.cpp

CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/v1rushb/newDev/newCopyCryptanalysis/src/IEncrypt.cpp > CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.i

CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/v1rushb/newDev/newCopyCryptanalysis/src/IEncrypt.cpp -o CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.s

# Object files for target CryptoGraphix
CryptoGraphix_OBJECTS = \
"CMakeFiles/CryptoGraphix.dir/src/main.cpp.o" \
"CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o" \
"CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o" \
"CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o" \
"CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o"

# External object files for target CryptoGraphix
CryptoGraphix_EXTERNAL_OBJECTS =

bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/src/main.cpp.o
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/src/ImageReader.cpp.o
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/src/ImageWriter.cpp.o
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/src/AES256Encryption.cpp.o
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/src/IEncrypt.cpp.o
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/build.make
bin/CryptoGraphix: /usr/local/lib/libopencv_imgcodecs.so.4.9.0
bin/CryptoGraphix: /usr/local/lib/libopencv_imgproc.so.4.9.0
bin/CryptoGraphix: /usr/local/lib/libcryptopp.a
bin/CryptoGraphix: /usr/local/lib/libopencv_core.so.4.9.0
bin/CryptoGraphix: CMakeFiles/CryptoGraphix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable bin/CryptoGraphix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CryptoGraphix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CryptoGraphix.dir/build: bin/CryptoGraphix
.PHONY : CMakeFiles/CryptoGraphix.dir/build

CMakeFiles/CryptoGraphix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CryptoGraphix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CryptoGraphix.dir/clean

CMakeFiles/CryptoGraphix.dir/depend:
	cd /home/v1rushb/newDev/newCopyCryptanalysis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/v1rushb/newDev/newCopyCryptanalysis /home/v1rushb/newDev/newCopyCryptanalysis /home/v1rushb/newDev/newCopyCryptanalysis /home/v1rushb/newDev/newCopyCryptanalysis /home/v1rushb/newDev/newCopyCryptanalysis/CMakeFiles/CryptoGraphix.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CryptoGraphix.dir/depend

