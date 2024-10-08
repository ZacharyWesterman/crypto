# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/joe/coding/projects/crypto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe/coding/projects/crypto

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/joe/coding/projects/crypto/CMakeFiles /home/joe/coding/projects/crypto//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/joe/coding/projects/crypto/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ciphers

# Build rule for target.
ciphers: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ciphers
.PHONY : ciphers

# fast build rule for target.
ciphers/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/build
.PHONY : ciphers/fast

#=============================================================================
# Target rules for targets named helpers

# Build rule for target.
helpers: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 helpers
.PHONY : helpers

# fast build rule for target.
helpers/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/build
.PHONY : helpers/fast

#=============================================================================
# Target rules for targets named crypto

# Build rule for target.
crypto: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 crypto
.PHONY : crypto

# fast build rule for target.
crypto/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/crypto.dir/build.make CMakeFiles/crypto.dir/build
.PHONY : crypto/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named install_libzed

# Build rule for target.
install_libzed: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 install_libzed
.PHONY : install_libzed

# fast build rule for target.
install_libzed/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/install_libzed.dir/build.make CMakeFiles/install_libzed.dir/build
.PHONY : install_libzed/fast

#=============================================================================
# Target rules for targets named update_libzed

# Build rule for target.
update_libzed: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_libzed
.PHONY : update_libzed

# fast build rule for target.
update_libzed/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/update_libzed.dir/build.make CMakeFiles/update_libzed.dir/build
.PHONY : update_libzed/fast

#=============================================================================
# Target rules for targets named randomAnalyzer

# Build rule for target.
randomAnalyzer: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 randomAnalyzer
.PHONY : randomAnalyzer

# fast build rule for target.
randomAnalyzer/fast:
	$(MAKE) $(MAKESILENT) -f tools/analyzer/CMakeFiles/randomAnalyzer.dir/build.make tools/analyzer/CMakeFiles/randomAnalyzer.dir/build
.PHONY : randomAnalyzer/fast

#=============================================================================
# Target rules for targets named caesarAnalyzer

# Build rule for target.
caesarAnalyzer: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 caesarAnalyzer
.PHONY : caesarAnalyzer

# fast build rule for target.
caesarAnalyzer/fast:
	$(MAKE) $(MAKESILENT) -f tools/analyzer/CMakeFiles/caesarAnalyzer.dir/build.make tools/analyzer/CMakeFiles/caesarAnalyzer.dir/build
.PHONY : caesarAnalyzer/fast

#=============================================================================
# Target rules for targets named wikiAnalyzer

# Build rule for target.
wikiAnalyzer: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 wikiAnalyzer
.PHONY : wikiAnalyzer

# fast build rule for target.
wikiAnalyzer/fast:
	$(MAKE) $(MAKESILENT) -f tools/analyzer/CMakeFiles/wikiAnalyzer.dir/build.make tools/analyzer/CMakeFiles/wikiAnalyzer.dir/build
.PHONY : wikiAnalyzer/fast

#=============================================================================
# Target rules for targets named update_dict

# Build rule for target.
update_dict: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_dict
.PHONY : update_dict

# fast build rule for target.
update_dict/fast:
	$(MAKE) $(MAKESILENT) -f tools/update_dict/CMakeFiles/update_dict.dir/build.make tools/update_dict/CMakeFiles/update_dict.dir/build
.PHONY : update_dict/fast

#=============================================================================
# Target rules for targets named run_tests

# Build rule for target.
run_tests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 run_tests
.PHONY : run_tests

# fast build rule for target.
run_tests/fast:
	$(MAKE) $(MAKESILENT) -f tests/CMakeFiles/run_tests.dir/build.make tests/CMakeFiles/run_tests.dir/build
.PHONY : run_tests/fast

src/ciphers/caesar.o: src/ciphers/caesar.cpp.o
.PHONY : src/ciphers/caesar.o

# target to build an object file
src/ciphers/caesar.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/caesar.cpp.o
.PHONY : src/ciphers/caesar.cpp.o

src/ciphers/caesar.i: src/ciphers/caesar.cpp.i
.PHONY : src/ciphers/caesar.i

# target to preprocess a source file
src/ciphers/caesar.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/caesar.cpp.i
.PHONY : src/ciphers/caesar.cpp.i

src/ciphers/caesar.s: src/ciphers/caesar.cpp.s
.PHONY : src/ciphers/caesar.s

# target to generate assembly for a file
src/ciphers/caesar.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/caesar.cpp.s
.PHONY : src/ciphers/caesar.cpp.s

src/ciphers/substitution.o: src/ciphers/substitution.cpp.o
.PHONY : src/ciphers/substitution.o

# target to build an object file
src/ciphers/substitution.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/substitution.cpp.o
.PHONY : src/ciphers/substitution.cpp.o

src/ciphers/substitution.i: src/ciphers/substitution.cpp.i
.PHONY : src/ciphers/substitution.i

# target to preprocess a source file
src/ciphers/substitution.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/substitution.cpp.i
.PHONY : src/ciphers/substitution.cpp.i

src/ciphers/substitution.s: src/ciphers/substitution.cpp.s
.PHONY : src/ciphers/substitution.s

# target to generate assembly for a file
src/ciphers/substitution.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ciphers.dir/build.make CMakeFiles/ciphers.dir/src/ciphers/substitution.cpp.s
.PHONY : src/ciphers/substitution.cpp.s

src/crypto.o: src/crypto.cpp.o
.PHONY : src/crypto.o

# target to build an object file
src/crypto.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/crypto.dir/build.make CMakeFiles/crypto.dir/src/crypto.cpp.o
.PHONY : src/crypto.cpp.o

src/crypto.i: src/crypto.cpp.i
.PHONY : src/crypto.i

# target to preprocess a source file
src/crypto.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/crypto.dir/build.make CMakeFiles/crypto.dir/src/crypto.cpp.i
.PHONY : src/crypto.cpp.i

src/crypto.s: src/crypto.cpp.s
.PHONY : src/crypto.s

# target to generate assembly for a file
src/crypto.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/crypto.dir/build.make CMakeFiles/crypto.dir/src/crypto.cpp.s
.PHONY : src/crypto.cpp.s

src/helpers/dictionary.o: src/helpers/dictionary.cpp.o
.PHONY : src/helpers/dictionary.o

# target to build an object file
src/helpers/dictionary.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/dictionary.cpp.o
.PHONY : src/helpers/dictionary.cpp.o

src/helpers/dictionary.i: src/helpers/dictionary.cpp.i
.PHONY : src/helpers/dictionary.i

# target to preprocess a source file
src/helpers/dictionary.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/dictionary.cpp.i
.PHONY : src/helpers/dictionary.cpp.i

src/helpers/dictionary.s: src/helpers/dictionary.cpp.s
.PHONY : src/helpers/dictionary.s

# target to generate assembly for a file
src/helpers/dictionary.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/dictionary.cpp.s
.PHONY : src/helpers/dictionary.cpp.s

src/helpers/parser.o: src/helpers/parser.cpp.o
.PHONY : src/helpers/parser.o

# target to build an object file
src/helpers/parser.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/parser.cpp.o
.PHONY : src/helpers/parser.cpp.o

src/helpers/parser.i: src/helpers/parser.cpp.i
.PHONY : src/helpers/parser.i

# target to preprocess a source file
src/helpers/parser.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/parser.cpp.i
.PHONY : src/helpers/parser.cpp.i

src/helpers/parser.s: src/helpers/parser.cpp.s
.PHONY : src/helpers/parser.s

# target to generate assembly for a file
src/helpers/parser.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/helpers.dir/build.make CMakeFiles/helpers.dir/src/helpers/parser.cpp.s
.PHONY : src/helpers/parser.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... install_libzed"
	@echo "... test"
	@echo "... update_libzed"
	@echo "... caesarAnalyzer"
	@echo "... ciphers"
	@echo "... crypto"
	@echo "... helpers"
	@echo "... randomAnalyzer"
	@echo "... run_tests"
	@echo "... update_dict"
	@echo "... wikiAnalyzer"
	@echo "... src/ciphers/caesar.o"
	@echo "... src/ciphers/caesar.i"
	@echo "... src/ciphers/caesar.s"
	@echo "... src/ciphers/substitution.o"
	@echo "... src/ciphers/substitution.i"
	@echo "... src/ciphers/substitution.s"
	@echo "... src/crypto.o"
	@echo "... src/crypto.i"
	@echo "... src/crypto.s"
	@echo "... src/helpers/dictionary.o"
	@echo "... src/helpers/dictionary.i"
	@echo "... src/helpers/dictionary.s"
	@echo "... src/helpers/parser.o"
	@echo "... src/helpers/parser.i"
	@echo "... src/helpers/parser.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

