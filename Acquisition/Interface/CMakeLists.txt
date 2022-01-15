add_library(PixieInterface SHARED source/PixieInterface.cpp source/Lock.cpp source/PixieSupport.cpp source/Utility.cpp)
target_include_directories(PixieInterface PUBLIC include ${PROJECT_SOURCE_DIR}/Core/include ${PIXIESDK_INCLUDE_DIR})
target_link_directories(PixieInterface PUBLIC ${PIXIESDK_LIBRARY_DIR} ${PLX_LIBRARY_DIR})
target_link_libraries(PixieInterface PaassCore Pixie16Api ${PLX_STATIC_LIB})
target_compile_options(PixieInterface PRIVATE "-DPLX_LINUX")

file(GLOB PIXIE_INTERFACE_PUBLIC_HEADERS include/*.h)
set_target_properties(PixieInterface PROPERTIES PUBLIC_HEADER "${PIXIE_INTERFACE_PUBLIC_HEADERS}")
install(TARGETS PixieInterface LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)