add_executable(tests tests.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/doctest include ${ROOT_INCLUDE_DIR}
        ${GSL_INCLUDE_DIR})
target_link_libraries(tests PUBLIC ${ROOT_LIBRARIES} ${GSL_LIBRARIES})

add_subdirectory(functional)
#add_subdirectory(integration)
add_subdirectory(unit)
