add_executable(tests tests.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/doctest ${TEST_INCLUDE_DIRECTORIES})

add_subdirectory(unit/analysis/resources)

add_test(TestSuite tests)