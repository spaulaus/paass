add_executable(set2ascii source/set2root.cpp)
target_include_directories(set2ascii PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include)
install(TARGETS set2ascii DESTINATION bin)

add_executable(set2root source/set2root.cpp)
set_target_properties(set2root PROPERTIES COMPILE_FLAGS "-DUSE_ROOT_OUTPUT")
target_include_directories(set2root PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include ${ROOT_INCLUDE_DIR})
target_link_libraries(set2root ${ROOT_LIBRARIES})
install(TARGETS set2root DESTINATION bin)
