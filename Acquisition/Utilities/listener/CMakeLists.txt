add_executable(listener source/listener.cpp)
target_include_directories(listener PUBLIC ${PROJECT_SOURCE_DIR}/Core/include)
target_link_libraries(listener PaassCore)
install(TARGETS listener DESTINATION bin)