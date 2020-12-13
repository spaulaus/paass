add_executable(monitor source/monitor.cpp)
target_include_directories(monitor PUBLIC ${PROJECT_SOURCE_DIR}/Core/include
        ${PROJECT_SOURCE_DIR}/Acquisition/Poll/include)
target_link_libraries(monitor PollServer PaassCore)
install(TARGETS monitor DESTINATION bin)
install(FILES bin/monitor.bash DESTINATION bin)