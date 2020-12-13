add_executable(listener source/listener.cpp)
target_include_directories(listener PUBLIC ${PROJECT_SOURCE_DIR}/Acquisition/Poll/include)
target_link_libraries(listener PollServer)
install(TARGETS listener DESTINATION bin)