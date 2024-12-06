cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS ON)

project(taller_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
    )

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

#option(DBG_LOG "Enable / disable tests." ON)
#if(DBG_LOG)
#     SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DLOG_DBG")
#endif()

# Define target: lib common between client, server and editor programs
# HEY TODO XXX: change the name to something that you like
add_library(taller_common STATIC)

# add the source files that make the lib
# HEY!! TODO XXX: add more subfolders here
add_subdirectory(common/)


# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(taller_common PUBLIC .)

# Install libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        libSDL2pp
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
    set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
    set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
    find_package(SDL2pp REQUIRED)
    
    add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/res")
    
    FetchContent_MakeAvailable(libSDL2pp)

    # Activa la generación automática de archivos de encabezado a partir de archivos .ui
    set(CMAKE_AUTOUIC ON)
    # Activa la generación automática de código de metaobjetos (MOC) para las clases que utilizan señales y slots en Qt
    set(CMAKE_AUTOMOC ON)
    # Permite la generación automática de archivos de encabezado a partir de archivos .qrc
    set(CMAKE_AUTORCC ON)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
endif()

if(TALLER_EDITOR OR TALLER_SERVER OR TALLER_TESTS)
	# Fetch rapid yaml	
	include(FetchContent)

	FetchContent_Declare(ryml #yaml-cpp
	    GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
	    GIT_TAG master
	    GIT_SHALLOW FALSE  # ensure submodules are checked out
	    #GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git # yaml version...
	)
	FetchContent_MakeAvailable(ryml)
	
	
	# Create serial lib
	add_library(taller_serial)
	add_subdirectory(serial/)
	
	#add_dependencies(taller_serial yaml-cpp::yaml-cpp)
	target_link_libraries(taller_serial PUBLIC taller_common ryml::ryml)#yaml-cpp::yaml-cpp) 
	
	add_executable(taller_dbg serial/main_dbg.cpp)
	add_dependencies(taller_dbg taller_serial)
	target_link_libraries(taller_dbg taller_serial)
	
	
	# Si es el server o tests. Entonces separa la lib de logica del server       
	if(TALLER_SERVER OR TALLER_TESTS)
	    # Lets load logic of server.
	    add_library(taller_server_logic)
	    add_subdirectory(server/)
	    #add_subdirectory(server/logic_server/)

	    # Make them depend on taller_common lib
	    add_dependencies(taller_server_logic taller_common taller_serial)
	    target_link_libraries(taller_server_logic taller_common taller_serial)
	endif()
	
endif()





# Program section
# ---------------
if(TALLER_CLIENT)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(taller_client)

    # Make them depend on taller_common lib
    add_dependencies(taller_client taller_common SDL2pp::SDL2pp)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(client)

    set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(taller_client PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(taller_client taller_common
        SDL2pp::SDL2pp
        Qt${QT_VERSION_MAJOR}::Widgets
    )
endif()



if(TALLER_SERVER)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(taller_server server/main.cpp)

    # Make them depend on taller_common lib
    add_dependencies(taller_server taller_common taller_server_logic)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    
    # Only executable is main.cpp, allows for using server folder as library.. for testing.
    #add_subdirectory(server)

    set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the taller_common lib target
    target_link_libraries(taller_server taller_common taller_server_logic)
endif()

if(TALLER_EDITOR)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(taller_editor)

    # Make them depend on taller_common lib
    add_dependencies(taller_editor taller_common taller_serial SDL2pp::SDL2pp)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(editor)

    set_project_warnings(taller_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(taller_editor PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(taller_editor taller_common taller_serial SDL2pp::SDL2pp Qt${QT_VERSION_MAJOR}::Widgets)
endif()


# Testing section
# ---------------



if(TALLER_TESTS)

function(
  link_to_gtest
  target_name)
    message("---Linking gtest to " ${target_name})
    
    # Say where to find the xoz headers
    # HEY!! TODO XXX: add more subfolders here
    target_include_directories(${target_name} PUBLIC .)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(${target_name} ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Say where googletest headers can be found
    target_include_directories(${target_name}
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
        )

    # HEY!! TODO XXX: I'm assuming that the code under testing is in taller_common
    # Change this if you have to.
    target_link_libraries(${target_name}
        GTest::gtest_main
        gmock_main
    )  
endfunction()  

    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    
    
    add_library(testers_core STATIC)

    # target for testing
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(tester_protocol)
    add_executable(tester_logic)
    add_executable(tester_integration)

    add_subdirectory(tests/)
    
    # Add depedencies to respective items
    add_dependencies(testers_core taller_common taller_serial)
    target_link_libraries(testers_core taller_common taller_serial)
    
    
    add_dependencies(tester_protocol testers_core)
    add_dependencies(tester_logic testers_core taller_server_logic)
    add_dependencies(tester_integration testers_core taller_server_logic)

    link_to_gtest(testers_core)

    link_to_gtest(tester_protocol)
    target_link_libraries(tester_protocol testers_core)
    
    link_to_gtest(tester_logic)
    target_link_libraries(tester_logic testers_core taller_server_logic)

    link_to_gtest(tester_integration)
    target_link_libraries(tester_integration testers_core taller_server_logic)
    
endif()
