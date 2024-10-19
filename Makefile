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
CMAKE_SOURCE_DIR = /home/marcelo-origoni/Documents/taller/grupal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcelo-origoni/Documents/taller/grupal

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

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/marcelo-origoni/Documents/taller/grupal/CMakeFiles /home/marcelo-origoni/Documents/taller/grupal//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/marcelo-origoni/Documents/taller/grupal/CMakeFiles 0
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
# Target rules for targets named taller_common

# Build rule for target.
taller_common: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 taller_common
.PHONY : taller_common

# fast build rule for target.
taller_common/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/build
.PHONY : taller_common/fast

#=============================================================================
# Target rules for targets named taller_client

# Build rule for target.
taller_client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 taller_client
.PHONY : taller_client

# fast build rule for target.
taller_client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/build
.PHONY : taller_client/fast

#=============================================================================
# Target rules for targets named taller_server

# Build rule for target.
taller_server: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 taller_server
.PHONY : taller_server

# fast build rule for target.
taller_server/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/build
.PHONY : taller_server/fast

#=============================================================================
# Target rules for targets named taller_editor

# Build rule for target.
taller_editor: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 taller_editor
.PHONY : taller_editor

# fast build rule for target.
taller_editor/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_editor.dir/build.make CMakeFiles/taller_editor.dir/build
.PHONY : taller_editor/fast

#=============================================================================
# Target rules for targets named taller_tests

# Build rule for target.
taller_tests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 taller_tests
.PHONY : taller_tests

# fast build rule for target.
taller_tests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_tests.dir/build.make CMakeFiles/taller_tests.dir/build
.PHONY : taller_tests/fast

#=============================================================================
# Target rules for targets named SDL2pp

# Build rule for target.
SDL2pp: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SDL2pp
.PHONY : SDL2pp

# fast build rule for target.
SDL2pp/fast:
	$(MAKE) $(MAKESILENT) -f _deps/libsdl2pp-build/CMakeFiles/SDL2pp.dir/build.make _deps/libsdl2pp-build/CMakeFiles/SDL2pp.dir/build
.PHONY : SDL2pp/fast

#=============================================================================
# Target rules for targets named gmock

# Build rule for target.
gmock: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gmock
.PHONY : gmock

# fast build rule for target.
gmock/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build
.PHONY : gmock/fast

#=============================================================================
# Target rules for targets named gmock_main

# Build rule for target.
gmock_main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gmock_main
.PHONY : gmock_main

# fast build rule for target.
gmock_main/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build
.PHONY : gmock_main/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

client/client.o: client/client.cpp.o
.PHONY : client/client.o

# target to build an object file
client/client.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/client.cpp.o
.PHONY : client/client.cpp.o

client/client.i: client/client.cpp.i
.PHONY : client/client.i

# target to preprocess a source file
client/client.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/client.cpp.i
.PHONY : client/client.cpp.i

client/client.s: client/client.cpp.s
.PHONY : client/client.s

# target to generate assembly for a file
client/client.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/client.cpp.s
.PHONY : client/client.cpp.s

client/clientprotocol.o: client/clientprotocol.cpp.o
.PHONY : client/clientprotocol.o

# target to build an object file
client/clientprotocol.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/clientprotocol.cpp.o
.PHONY : client/clientprotocol.cpp.o

client/clientprotocol.i: client/clientprotocol.cpp.i
.PHONY : client/clientprotocol.i

# target to preprocess a source file
client/clientprotocol.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/clientprotocol.cpp.i
.PHONY : client/clientprotocol.cpp.i

client/clientprotocol.s: client/clientprotocol.cpp.s
.PHONY : client/clientprotocol.s

# target to generate assembly for a file
client/clientprotocol.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/clientprotocol.cpp.s
.PHONY : client/clientprotocol.cpp.s

client/main.o: client/main.cpp.o
.PHONY : client/main.o

# target to build an object file
client/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/main.cpp.o
.PHONY : client/main.cpp.o

client/main.i: client/main.cpp.i
.PHONY : client/main.i

# target to preprocess a source file
client/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/main.cpp.i
.PHONY : client/main.cpp.i

client/main.s: client/main.cpp.s
.PHONY : client/main.s

# target to generate assembly for a file
client/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_client.dir/build.make CMakeFiles/taller_client.dir/client/main.cpp.s
.PHONY : client/main.cpp.s

common/event.o: common/event.cpp.o
.PHONY : common/event.o

# target to build an object file
common/event.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/event.cpp.o
.PHONY : common/event.cpp.o

common/event.i: common/event.cpp.i
.PHONY : common/event.i

# target to preprocess a source file
common/event.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/event.cpp.i
.PHONY : common/event.cpp.i

common/event.s: common/event.cpp.s
.PHONY : common/event.s

# target to generate assembly for a file
common/event.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/event.cpp.s
.PHONY : common/event.cpp.s

common/liberror.o: common/liberror.cpp.o
.PHONY : common/liberror.o

# target to build an object file
common/liberror.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/liberror.cpp.o
.PHONY : common/liberror.cpp.o

common/liberror.i: common/liberror.cpp.i
.PHONY : common/liberror.i

# target to preprocess a source file
common/liberror.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/liberror.cpp.i
.PHONY : common/liberror.cpp.i

common/liberror.s: common/liberror.cpp.s
.PHONY : common/liberror.s

# target to generate assembly for a file
common/liberror.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/liberror.cpp.s
.PHONY : common/liberror.cpp.s

common/protocol.o: common/protocol.cpp.o
.PHONY : common/protocol.o

# target to build an object file
common/protocol.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/protocol.cpp.o
.PHONY : common/protocol.cpp.o

common/protocol.i: common/protocol.cpp.i
.PHONY : common/protocol.i

# target to preprocess a source file
common/protocol.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/protocol.cpp.i
.PHONY : common/protocol.cpp.i

common/protocol.s: common/protocol.cpp.s
.PHONY : common/protocol.s

# target to generate assembly for a file
common/protocol.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/protocol.cpp.s
.PHONY : common/protocol.cpp.s

common/resolver.o: common/resolver.cpp.o
.PHONY : common/resolver.o

# target to build an object file
common/resolver.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolver.cpp.o
.PHONY : common/resolver.cpp.o

common/resolver.i: common/resolver.cpp.i
.PHONY : common/resolver.i

# target to preprocess a source file
common/resolver.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolver.cpp.i
.PHONY : common/resolver.cpp.i

common/resolver.s: common/resolver.cpp.s
.PHONY : common/resolver.s

# target to generate assembly for a file
common/resolver.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolver.cpp.s
.PHONY : common/resolver.cpp.s

common/resolvererror.o: common/resolvererror.cpp.o
.PHONY : common/resolvererror.o

# target to build an object file
common/resolvererror.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolvererror.cpp.o
.PHONY : common/resolvererror.cpp.o

common/resolvererror.i: common/resolvererror.cpp.i
.PHONY : common/resolvererror.i

# target to preprocess a source file
common/resolvererror.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolvererror.cpp.i
.PHONY : common/resolvererror.cpp.i

common/resolvererror.s: common/resolvererror.cpp.s
.PHONY : common/resolvererror.s

# target to generate assembly for a file
common/resolvererror.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/resolvererror.cpp.s
.PHONY : common/resolvererror.cpp.s

common/reward.o: common/reward.cpp.o
.PHONY : common/reward.o

# target to build an object file
common/reward.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/reward.cpp.o
.PHONY : common/reward.cpp.o

common/reward.i: common/reward.cpp.i
.PHONY : common/reward.i

# target to preprocess a source file
common/reward.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/reward.cpp.i
.PHONY : common/reward.cpp.i

common/reward.s: common/reward.cpp.s
.PHONY : common/reward.s

# target to generate assembly for a file
common/reward.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/reward.cpp.s
.PHONY : common/reward.cpp.s

common/socket.o: common/socket.cpp.o
.PHONY : common/socket.o

# target to build an object file
common/socket.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/socket.cpp.o
.PHONY : common/socket.cpp.o

common/socket.i: common/socket.cpp.i
.PHONY : common/socket.i

# target to preprocess a source file
common/socket.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/socket.cpp.i
.PHONY : common/socket.cpp.i

common/socket.s: common/socket.cpp.s
.PHONY : common/socket.s

# target to generate assembly for a file
common/socket.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_common.dir/build.make CMakeFiles/taller_common.dir/common/socket.cpp.s
.PHONY : common/socket.cpp.s

editor/main.o: editor/main.cpp.o
.PHONY : editor/main.o

# target to build an object file
editor/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_editor.dir/build.make CMakeFiles/taller_editor.dir/editor/main.cpp.o
.PHONY : editor/main.cpp.o

editor/main.i: editor/main.cpp.i
.PHONY : editor/main.i

# target to preprocess a source file
editor/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_editor.dir/build.make CMakeFiles/taller_editor.dir/editor/main.cpp.i
.PHONY : editor/main.cpp.i

editor/main.s: editor/main.cpp.s
.PHONY : editor/main.s

# target to generate assembly for a file
editor/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_editor.dir/build.make CMakeFiles/taller_editor.dir/editor/main.cpp.s
.PHONY : editor/main.cpp.s

server/box.o: server/box.cpp.o
.PHONY : server/box.o

# target to build an object file
server/box.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/box.cpp.o
.PHONY : server/box.cpp.o

server/box.i: server/box.cpp.i
.PHONY : server/box.i

# target to preprocess a source file
server/box.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/box.cpp.i
.PHONY : server/box.cpp.i

server/box.s: server/box.cpp.s
.PHONY : server/box.s

# target to generate assembly for a file
server/box.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/box.cpp.s
.PHONY : server/box.cpp.s

server/gameerror.o: server/gameerror.cpp.o
.PHONY : server/gameerror.o

# target to build an object file
server/gameerror.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/gameerror.cpp.o
.PHONY : server/gameerror.cpp.o

server/gameerror.i: server/gameerror.cpp.i
.PHONY : server/gameerror.i

# target to preprocess a source file
server/gameerror.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/gameerror.cpp.i
.PHONY : server/gameerror.cpp.i

server/gameerror.s: server/gameerror.cpp.s
.PHONY : server/gameerror.s

# target to generate assembly for a file
server/gameerror.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/gameerror.cpp.s
.PHONY : server/gameerror.cpp.s

server/lobbycontainer.o: server/lobbycontainer.cpp.o
.PHONY : server/lobbycontainer.o

# target to build an object file
server/lobbycontainer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/lobbycontainer.cpp.o
.PHONY : server/lobbycontainer.cpp.o

server/lobbycontainer.i: server/lobbycontainer.cpp.i
.PHONY : server/lobbycontainer.i

# target to preprocess a source file
server/lobbycontainer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/lobbycontainer.cpp.i
.PHONY : server/lobbycontainer.cpp.i

server/lobbycontainer.s: server/lobbycontainer.cpp.s
.PHONY : server/lobbycontainer.s

# target to generate assembly for a file
server/lobbycontainer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/lobbycontainer.cpp.s
.PHONY : server/lobbycontainer.cpp.s

server/main.o: server/main.cpp.o
.PHONY : server/main.o

# target to build an object file
server/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/main.cpp.o
.PHONY : server/main.cpp.o

server/main.i: server/main.cpp.i
.PHONY : server/main.i

# target to preprocess a source file
server/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/main.cpp.i
.PHONY : server/main.cpp.i

server/main.s: server/main.cpp.s
.PHONY : server/main.s

# target to generate assembly for a file
server/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/main.cpp.s
.PHONY : server/main.cpp.s

server/match.o: server/match.cpp.o
.PHONY : server/match.o

# target to build an object file
server/match.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/match.cpp.o
.PHONY : server/match.cpp.o

server/match.i: server/match.cpp.i
.PHONY : server/match.i

# target to preprocess a source file
server/match.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/match.cpp.i
.PHONY : server/match.cpp.i

server/match.s: server/match.cpp.s
.PHONY : server/match.s

# target to generate assembly for a file
server/match.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/match.cpp.s
.PHONY : server/match.cpp.s

server/matchaction.o: server/matchaction.cpp.o
.PHONY : server/matchaction.o

# target to build an object file
server/matchaction.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchaction.cpp.o
.PHONY : server/matchaction.cpp.o

server/matchaction.i: server/matchaction.cpp.i
.PHONY : server/matchaction.i

# target to preprocess a source file
server/matchaction.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchaction.cpp.i
.PHONY : server/matchaction.cpp.i

server/matchaction.s: server/matchaction.cpp.s
.PHONY : server/matchaction.s

# target to generate assembly for a file
server/matchaction.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchaction.cpp.s
.PHONY : server/matchaction.cpp.s

server/matchqueue.o: server/matchqueue.cpp.o
.PHONY : server/matchqueue.o

# target to build an object file
server/matchqueue.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchqueue.cpp.o
.PHONY : server/matchqueue.cpp.o

server/matchqueue.i: server/matchqueue.cpp.i
.PHONY : server/matchqueue.i

# target to preprocess a source file
server/matchqueue.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchqueue.cpp.i
.PHONY : server/matchqueue.cpp.i

server/matchqueue.s: server/matchqueue.cpp.s
.PHONY : server/matchqueue.s

# target to generate assembly for a file
server/matchqueue.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchqueue.cpp.s
.PHONY : server/matchqueue.cpp.s

server/matchserver.o: server/matchserver.cpp.o
.PHONY : server/matchserver.o

# target to build an object file
server/matchserver.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchserver.cpp.o
.PHONY : server/matchserver.cpp.o

server/matchserver.i: server/matchserver.cpp.i
.PHONY : server/matchserver.i

# target to preprocess a source file
server/matchserver.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchserver.cpp.i
.PHONY : server/matchserver.cpp.i

server/matchserver.s: server/matchserver.cpp.s
.PHONY : server/matchserver.s

# target to generate assembly for a file
server/matchserver.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchserver.cpp.s
.PHONY : server/matchserver.cpp.s

server/matchstate.o: server/matchstate.cpp.o
.PHONY : server/matchstate.o

# target to build an object file
server/matchstate.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchstate.cpp.o
.PHONY : server/matchstate.cpp.o

server/matchstate.i: server/matchstate.cpp.i
.PHONY : server/matchstate.i

# target to preprocess a source file
server/matchstate.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchstate.cpp.i
.PHONY : server/matchstate.cpp.i

server/matchstate.s: server/matchstate.cpp.s
.PHONY : server/matchstate.s

# target to generate assembly for a file
server/matchstate.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/matchstate.cpp.s
.PHONY : server/matchstate.cpp.s

server/player.o: server/player.cpp.o
.PHONY : server/player.o

# target to build an object file
server/player.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/player.cpp.o
.PHONY : server/player.cpp.o

server/player.i: server/player.cpp.i
.PHONY : server/player.i

# target to preprocess a source file
server/player.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/player.cpp.i
.PHONY : server/player.cpp.i

server/player.s: server/player.cpp.s
.PHONY : server/player.s

# target to generate assembly for a file
server/player.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/player.cpp.s
.PHONY : server/player.cpp.s

server/playeracceptor.o: server/playeracceptor.cpp.o
.PHONY : server/playeracceptor.o

# target to build an object file
server/playeracceptor.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playeracceptor.cpp.o
.PHONY : server/playeracceptor.cpp.o

server/playeracceptor.i: server/playeracceptor.cpp.i
.PHONY : server/playeracceptor.i

# target to preprocess a source file
server/playeracceptor.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playeracceptor.cpp.i
.PHONY : server/playeracceptor.cpp.i

server/playeracceptor.s: server/playeracceptor.cpp.s
.PHONY : server/playeracceptor.s

# target to generate assembly for a file
server/playeracceptor.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playeracceptor.cpp.s
.PHONY : server/playeracceptor.cpp.s

server/playercontainer.o: server/playercontainer.cpp.o
.PHONY : server/playercontainer.o

# target to build an object file
server/playercontainer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontainer.cpp.o
.PHONY : server/playercontainer.cpp.o

server/playercontainer.i: server/playercontainer.cpp.i
.PHONY : server/playercontainer.i

# target to preprocess a source file
server/playercontainer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontainer.cpp.i
.PHONY : server/playercontainer.cpp.i

server/playercontainer.s: server/playercontainer.cpp.s
.PHONY : server/playercontainer.s

# target to generate assembly for a file
server/playercontainer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontainer.cpp.s
.PHONY : server/playercontainer.cpp.s

server/playercontroller.o: server/playercontroller.cpp.o
.PHONY : server/playercontroller.o

# target to build an object file
server/playercontroller.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontroller.cpp.o
.PHONY : server/playercontroller.cpp.o

server/playercontroller.i: server/playercontroller.cpp.i
.PHONY : server/playercontroller.i

# target to preprocess a source file
server/playercontroller.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontroller.cpp.i
.PHONY : server/playercontroller.cpp.i

server/playercontroller.s: server/playercontroller.cpp.s
.PHONY : server/playercontroller.s

# target to generate assembly for a file
server/playercontroller.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playercontroller.cpp.s
.PHONY : server/playercontroller.cpp.s

server/playernotifier.o: server/playernotifier.cpp.o
.PHONY : server/playernotifier.o

# target to build an object file
server/playernotifier.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playernotifier.cpp.o
.PHONY : server/playernotifier.cpp.o

server/playernotifier.i: server/playernotifier.cpp.i
.PHONY : server/playernotifier.i

# target to preprocess a source file
server/playernotifier.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playernotifier.cpp.i
.PHONY : server/playernotifier.cpp.i

server/playernotifier.s: server/playernotifier.cpp.s
.PHONY : server/playernotifier.s

# target to generate assembly for a file
server/playernotifier.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playernotifier.cpp.s
.PHONY : server/playernotifier.cpp.s

server/playerprotocol.o: server/playerprotocol.cpp.o
.PHONY : server/playerprotocol.o

# target to build an object file
server/playerprotocol.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playerprotocol.cpp.o
.PHONY : server/playerprotocol.cpp.o

server/playerprotocol.i: server/playerprotocol.cpp.i
.PHONY : server/playerprotocol.i

# target to preprocess a source file
server/playerprotocol.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playerprotocol.cpp.i
.PHONY : server/playerprotocol.cpp.i

server/playerprotocol.s: server/playerprotocol.cpp.s
.PHONY : server/playerprotocol.s

# target to generate assembly for a file
server/playerprotocol.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_server.dir/build.make CMakeFiles/taller_server.dir/server/playerprotocol.cpp.s
.PHONY : server/playerprotocol.cpp.s

tests/foo.o: tests/foo.cpp.o
.PHONY : tests/foo.o

# target to build an object file
tests/foo.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_tests.dir/build.make CMakeFiles/taller_tests.dir/tests/foo.cpp.o
.PHONY : tests/foo.cpp.o

tests/foo.i: tests/foo.cpp.i
.PHONY : tests/foo.i

# target to preprocess a source file
tests/foo.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_tests.dir/build.make CMakeFiles/taller_tests.dir/tests/foo.cpp.i
.PHONY : tests/foo.cpp.i

tests/foo.s: tests/foo.cpp.s
.PHONY : tests/foo.s

# target to generate assembly for a file
tests/foo.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/taller_tests.dir/build.make CMakeFiles/taller_tests.dir/tests/foo.cpp.s
.PHONY : tests/foo.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... SDL2pp"
	@echo "... gmock"
	@echo "... gmock_main"
	@echo "... gtest"
	@echo "... gtest_main"
	@echo "... taller_client"
	@echo "... taller_common"
	@echo "... taller_editor"
	@echo "... taller_server"
	@echo "... taller_tests"
	@echo "... client/client.o"
	@echo "... client/client.i"
	@echo "... client/client.s"
	@echo "... client/clientprotocol.o"
	@echo "... client/clientprotocol.i"
	@echo "... client/clientprotocol.s"
	@echo "... client/main.o"
	@echo "... client/main.i"
	@echo "... client/main.s"
	@echo "... common/event.o"
	@echo "... common/event.i"
	@echo "... common/event.s"
	@echo "... common/liberror.o"
	@echo "... common/liberror.i"
	@echo "... common/liberror.s"
	@echo "... common/protocol.o"
	@echo "... common/protocol.i"
	@echo "... common/protocol.s"
	@echo "... common/resolver.o"
	@echo "... common/resolver.i"
	@echo "... common/resolver.s"
	@echo "... common/resolvererror.o"
	@echo "... common/resolvererror.i"
	@echo "... common/resolvererror.s"
	@echo "... common/reward.o"
	@echo "... common/reward.i"
	@echo "... common/reward.s"
	@echo "... common/socket.o"
	@echo "... common/socket.i"
	@echo "... common/socket.s"
	@echo "... editor/main.o"
	@echo "... editor/main.i"
	@echo "... editor/main.s"
	@echo "... server/box.o"
	@echo "... server/box.i"
	@echo "... server/box.s"
	@echo "... server/gameerror.o"
	@echo "... server/gameerror.i"
	@echo "... server/gameerror.s"
	@echo "... server/lobbycontainer.o"
	@echo "... server/lobbycontainer.i"
	@echo "... server/lobbycontainer.s"
	@echo "... server/main.o"
	@echo "... server/main.i"
	@echo "... server/main.s"
	@echo "... server/match.o"
	@echo "... server/match.i"
	@echo "... server/match.s"
	@echo "... server/matchaction.o"
	@echo "... server/matchaction.i"
	@echo "... server/matchaction.s"
	@echo "... server/matchqueue.o"
	@echo "... server/matchqueue.i"
	@echo "... server/matchqueue.s"
	@echo "... server/matchserver.o"
	@echo "... server/matchserver.i"
	@echo "... server/matchserver.s"
	@echo "... server/matchstate.o"
	@echo "... server/matchstate.i"
	@echo "... server/matchstate.s"
	@echo "... server/player.o"
	@echo "... server/player.i"
	@echo "... server/player.s"
	@echo "... server/playeracceptor.o"
	@echo "... server/playeracceptor.i"
	@echo "... server/playeracceptor.s"
	@echo "... server/playercontainer.o"
	@echo "... server/playercontainer.i"
	@echo "... server/playercontainer.s"
	@echo "... server/playercontroller.o"
	@echo "... server/playercontroller.i"
	@echo "... server/playercontroller.s"
	@echo "... server/playernotifier.o"
	@echo "... server/playernotifier.i"
	@echo "... server/playernotifier.s"
	@echo "... server/playerprotocol.o"
	@echo "... server/playerprotocol.i"
	@echo "... server/playerprotocol.s"
	@echo "... tests/foo.o"
	@echo "... tests/foo.i"
	@echo "... tests/foo.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

