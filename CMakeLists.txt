cmake_minimum_required(VERSION 3.13)

project(PAASS)

#Use rpath on Mac OS
set(CMAKE_MACOSX_RPATH TRUE)

if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "7.0.0")
        message(FATAL_ERROR "GCC version 7+ required for regex support.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fPIC -fdiagnostics-color=auto")
endif ()

#if user does not specify prefix we assign it to the install directory
#@TODO I do not like the fact that it makes the install directory before I'm
#ready for it. There are cases where I do not want to actually install just
#build. This configuration adds additional junk to my directory that I may
#not actually want or need.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Install Prefix not specified.")
    file(MAKE_DIRECTORY install)
    get_filename_component(INSTALL_DIR ${CMAKE_BINARY_DIR}/../install REALPATH)
    set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE PATH "Install Prefix" FORCE)
endif ()
message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")

#Define the default build type to be Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Build type, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
    message(STATUS "Build type not defined, using default: ${CMAKE_BUILD_TYPE}")
endif (NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#Add additional CXX flags if we use the Debug option
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

#------------------------------------------------------------------------------
#We are going to include this additional module here since it could be useful
#when setting all of the following options.
include(CMakeDependentOption)

#Install options
option(PAASS_BUILD_ACQ "Build and install Acquisition software" ON)
option(PAASS_BUILD_ANALYSIS "Build analysis related programs" ON)
option(PAASS_BUILD_TESTS "Builds programs designed to test the package." OFF)

option(PAASS_EXPORT_COMPILE_COMMANDS "CMAKE_EXPORT_COMPILE_COMMANDS WRAPPER" ON)
mark_as_advanced(PAASS_EXPORT_COMPILE_COMMANDS)

#Generate the compile_commands.json file which is used by VSCode (among others) to generate the clang autocomplete
#Needs the PAASS_EXPORT_COMPILE_COMMANDS wrapper because of the "FORCE" which is required to even set the var from CMakeList.txt,
#while maintaining the ability to toggle it on/off without wiping the build dir
if(PAASS_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generates compile_commands.json, needed for some IDEs among other things" FORCE)
else ()
    set(CMAKE_EXPORT_COMPILE_COMMANDS OFF CACHE BOOL "Generates compile_commands.json, needed for some IDEs among other things" FORCE)   
endif (PAASS_EXPORT_COMPILE_COMMANDS)

#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/Cmake/modules/")

find_package(Threads REQUIRED)

find_package(Curses REQUIRED)
add_definitions("-D USE_NCURSES")
mark_as_advanced(FORCE CURSES_HAVE_CURSES_H CURSES_CURSES_H_PATH CURSES_FORM_LIBRARY)

find_package(ROOT REQUIRED COMPONENTS TreePlayer)
mark_as_advanced(FORCE GENREFLEX_EXECUTABLE ROOTCINT_EXECUTABLE ROOT_CONFIG_EXECUTABLE)
add_definitions("-D USE_ROOT")

find_package(GSL REQUIRED)
if (${GSL_VERSION} LESS 2.0)
    add_definitions("-D GSL_VERSION_ONE")
endif (${GSL_VERSION} LESS 2.0)

#if (PAASS_BUILD_TESTS)
#    add_subdirectory(Tests)
#    enable_testing()
#endif (PAASS_BUILD_TESTS)

#------------------------------------------------------------------------------
add_subdirectory(ThirdParty)
add_subdirectory(Resources)
add_subdirectory(Core)
add_subdirectory(Acquisition)
#if (PAASS_BUILD_ANALYSIS)
add_subdirectory(Analysis)
#endif (PAASS_BUILD_ANALYSIS)

#Build/install the miscellaneous stuff
#add_subdirectory(Share)
