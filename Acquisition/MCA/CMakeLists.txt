add_library(MCALibrary SHARED source/MCA.cpp source/MCA_ROOT.cpp)
target_include_directories(MCALibrary PUBLIC include ${PROJECT_SOURCE_DIR}/Acquisition/Interface/include ${ROOT_INCLUDE_DIR})
target_link_libraries(MCALibrary PixieInterface ${ROOT_LIBRARIES})

file(GLOB MCA_PUBLIC_HEADERS include/*.h)
set_target_properties(MCALibrary PROPERTIES PUBLIC_HEADER "${MCA_PUBLIC_HEADERS}")
install(TARGETS MCALibrary LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

add_executable(mca source/MCA_exec.cpp)
target_include_directories(mca PUBLIC include ${PROJECT_SOURCE_DIR}/Acquisition/Interface/include ${ROOT_INCLUDE_DIR})
target_link_libraries(mca PixieInterface MCALibrary ${ROOT_LIBRARIES})
install(TARGETS mca DESTINATION bin)
