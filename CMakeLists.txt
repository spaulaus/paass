cmake_minimum_required(VERSION 3.13)

project(paass)

if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "7.0.0")
        message(FATAL_ERROR "GCC version 7+ required for regex support.")
    endif ()
endif ()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME} CACHE PATH "..." FORCE)
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Build type, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
    message(STATUS "Build type not defined, using default: ${CMAKE_BUILD_TYPE}")
endif (NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#------------------------------------------------------------------------------

include(CMakeDependentOption)

option(PAASS_BUILD_ACQ "Build and install Acquisition software" ON)
option(PAASS_BUILD_ANALYSIS "Build analysis related programs" ON)
option(PAASS_BUILD_TESTS "Builds programs designed to test the package." OFF)

cmake_dependent_option(PAASS_BUILD_EVENT_READER "Program that outputs event information to the terminal" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_HEAD_READER "Program that outputs the header information from the file" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_HEX_READER "Program that outputs data as hex values" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_LIST_MODE_CONVERTER "Program to convert list-mode binary files to other file types." OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_ROOT_SCANNER "Program used for live scanning of files into ROOT hists" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_SCOPE "Program used to view traces in data stream" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_BUILD_SKELETON "Program that can be used as a template for custom analysis." OFF PAASS_BUILD_ANALYSIS OFF)

cmake_dependent_option(PAASS_BUILD_UTKSCAN "The primary analysis program" OFF PAASS_BUILD_ANALYSIS OFF)
cmake_dependent_option(PAASS_UTKSCAN_GAMMA_GATES "Gamma-Gamma gates in GeProcessor" OFF PAASS_BUILD_UTKSCAN OFF)
cmake_dependent_option(PAASS_UTKSCAN_ONLINE "Options for online scans" OFF PAASS_BUILD_UTKSCAN OFF)
cmake_dependent_option(PAASS_UTKSCAN_TREE_DEBUG "Debugging info for TreeCorrelator" OFF PAASS_BUILD_UTKSCAN OFF)
cmake_dependent_option(PAASS_UTKSCAN_VERBOSE "Make Scan More Verbose" OFF PAASS_BUILD_UTKSCAN OFF)

#------------------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generates compile_commands.json." FORCE)

#------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/Cmake/modules/" "$ENV{XIA_PIXIE_SDK}/cmake/modules")

find_package(Threads REQUIRED)

find_package(Curses REQUIRED)
add_definitions("-D USE_NCURSES")
mark_as_advanced(FORCE CURSES_HAVE_CURSES_H CURSES_CURSES_H_PATH CURSES_FORM_LIBRARY)

find_package(ROOT REQUIRED COMPONENTS TreePlayer)
mark_as_advanced(FORCE GENREFLEX_EXECUTABLE ROOTCINT_EXECUTABLE ROOT_CONFIG_EXECUTABLE)
add_definitions("-D USE_ROOT")

find_package(GSL REQUIRED)

if (PAASS_BUILD_LIST_MODE_CONVERTER)
    find_package(Arrow REQUIRED)
endif(PAASS_BUILD_LIST_MODE_CONVERTER)

#------------------------------------------------------------------------------

add_subdirectory(Acquisition)
add_subdirectory(Analysis)
add_subdirectory(Core)
add_subdirectory(Resources)
add_subdirectory(Share)
if (PAASS_BUILD_TESTS)
    add_subdirectory(Tests)
    enable_testing()
endif (PAASS_BUILD_TESTS)
add_subdirectory(ThirdParty)

#------------------------------------------------------------------------------

set(SO_LIBRARY_CONF_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.conf)
file(WRITE ${SO_LIBRARY_CONF_FILE} ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${SO_LIBRARY_CONF_FILE} DESTINATION etc/ld.so.conf.d/)
