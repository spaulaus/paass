add_executable(test_terminal source/test_terminal.cpp)
target_include_directories(test_terminal PUBLIC ${PROJECT_SOURCE_DIR}/Terminal/include)
target_link_libraries(test_terminal Terminal)