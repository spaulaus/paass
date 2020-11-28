add_executable(tests tests.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/doctest include)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/test_*.cpp)

add_subdirectory(unit/analysis/resources)
#add_subdirectory(unit/analysis/scan_libraries)
#add_subdirectory(unit/analysis/utkscan)
add_subdirectory(unit/resources)

add_test(TestSuite tests)