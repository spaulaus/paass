# Find the PLX Library
# @authors K. Smith, C. R. Thornsberry, S. V. Paulauskas
# Sets the usual variables expected for find_package scripts:
#
# PLX_LIBRARY_DIR - location of PLX library.
# PLX_LIBRARIES - list of libraries to be linked.
# PLX_FOUND - true if PLX was found.
#

find_path(PLX_LIBRARY_DIR
        NAMES PlxApi.a PlxApi.so
        HINTS $ENV{PLX_SDK_DIR}
        PATHS /usr/local/broadcom/current
        PATH_SUFFIXES PlxApi/Library Linux/PlxApi/Library)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PLX DEFAULT_MSG PLX_LIBRARY_DIR)

if (PLX_FOUND)
    set(PLX_SHARED_LIB -l:PlxApi.so -ldl)
    set(PLX_STATIC_LIB -l:PlxApi.a -ldl)
endif (PLX_FOUND)

mark_as_advanced(PLX_SHARED_LIB PLX_STATIC_LIB PLX_LIBRARY_DIR)
