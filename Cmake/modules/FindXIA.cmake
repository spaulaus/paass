# Find the XIA Library
#
# Sets the usual variables expected for find_package scripts:
#
# XIA_LIBRARY_DIR
# XIA_INCLUDE_DIR
# XIA_LIBRARIES
# XIA_FOUND - true if XIA was found.
# XIA_FIRMWARE_DIR - Directory to be searched for firmwares for pixie.cfg.
#
# Expected Structure:
#    - **/usr**
#      - **local/**
#        - **xia**
#          - **pixie**  - files provided by the XIA API
#            - **sdk**
#              - **lib** - API libraries
#              - **include**  - API includes
#            - **share**
#              - **pxisys** - contains the pxisys*.ini files provided in the API
#              - **slotdef** - probably just a single slot def, can be added to the API install
#            - **firmware**
#              - **2016-02-02-12b250m-vandle**  (and other specific firmware)
#                - **config** - not something that XIA distributes on their website, **DO NOT** add to repos
#                - **dsp**
#                - **fpga**
# @authors K. Smith, C. R. Thornsberry, S. V. Paulauskas

#Find the library path by looking for the library.
find_path(XIA_LIBRARY_DIR
        NAMES libPixie16App.so libPixie16Sys.so
        HINTS $ENV{XIA_PIXIE_SDK}
        PATHS /usr/local/xia/pixie/sdk
        PATH_SUFFIXES lib
        DOC "Path to pixie library.")

get_filename_component(XIA_LIBRARY_DIR "${XIA_LIBRARY_DIR}" REALPATH)

#Unset any cached value to ensure a fresh search is performed.
#This permits the user to change the XIA_FIRMWARE_DIR and have subsequent paths updated.
unset(XIA_FIRMWARE_DIR CACHE)

if (NOT XIA_FIRMWARE_DIR)
    get_filename_component(XIA_FIRMWARE_DIR "${XIA_LIBRARY_DIR}/../../firmware" REALPATH)
endif (NOT XIA_FIRMWARE_DIR)
set(XIA_FIRMWARE_DIR ${XIA_FIRMWARE_DIR} CACHE PATH "Path to folder containing XIA's Pixie firmware.")

find_path(XIA_APP_INCLUDES
        NAMES pixie16app_defs.h
        PATHS ${XIA_LIBRARY_DIR} "${XIA_LIBRARY_DIR}/../"
        PATH_SUFFIXES app include
        DOC "Path to XIA app includes.")
set(XIA_APP_INCLUDES ${XIA_APP_INCLUDES} CACHE INTERNAL "App includes")

find_path(XIA_SYS_INCLUDES
        NAMES pixie16sys_defs.h
        PATHS ${XIA_LIBRARY_DIR} "${XIA_LIBRARY_DIR}/../"
        PATH_SUFFIXES sys include
        DOC "Path to XIA sys includes.")
set(XIA_SYS_INCLUDES ${XIA_SYS_INCLUDES} CACHE INTERNAL "Sys Includes")

# Support the REQUIRED and QUIET arguments, and set XIA_FOUND if found.
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XIA DEFAULT_MSG XIA_LIBRARY_DIR)

if (XIA_FOUND)
    set(XIA_INCLUDE_DIR ${XIA_APP_INCLUDES} ${XIA_SYS_INCLUDES})
    list(REMOVE_DUPLICATES XIA_INCLUDE_DIR)
    set(XIA_LIBRARIES -lPixie16App -lPixie16Sys)
endif ()

