#Check if GSL is installed
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})
link_directories(${GSL_LIBRARY_DIRS})
if (${GSL_VERSION} LESS 2.0)
    add_definitions("-D GSL_VERSION_ONE")
endif (${GSL_VERSION} LESS 2.0)

add_executable(tests tests.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/doctest include)
target_link_libraries(tests PUBLIC ${ROOT_LIBRARIES} ${GSL_LIBRARIES})

add_subdirectory(unit/analysis/resources)
#add_subdirectory(unit/analysis/scan_libraries)
#add_subdirectory(unit/analysis/utkscan)
add_subdirectory(unit/resources)

add_test(Tests tests)