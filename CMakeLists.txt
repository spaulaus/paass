cmake_minimum_required(VERSION 3.13)

project(paass)

set(CMAKE_MACOSX_RPATH TRUE)

if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "7.0.0")
        message(FATAL_ERROR "GCC version 7+ required for regex support.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fPIC -fdiagnostics-color=auto")
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

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

#------------------------------------------------------------------------------

include(CMakeDependentOption)

option(PAASS_BUILD_ACQ "Build and install Acquisition software" ON)
option(PAASS_BUILD_ANALYSIS "Build analysis related programs" ON)
option(PAASS_BUILD_TESTS "Builds programs designed to test the package." ON)

#------------------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generates compile_commands.json." FORCE)

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
