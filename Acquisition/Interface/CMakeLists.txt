add_library(PixieInterface SHARED source/PixieInterface.cpp source/Lock.cpp source/PixieSupport.cpp source/Utility.cpp)
target_include_directories(PixieInterface PUBLIC include ${PROJECT_SOURCE_DIR}/Core/include ${XIA_INCLUDE_DIR})
target_link_directories(PixieInterface PUBLIC ${XIA_LIBRARY_DIR} ${PLX_LIBRARY_DIR})
target_link_libraries(PixieInterface PaassCore ${XIA_LIBRARIES} ${PLX_LIBRARIES})
target_compile_options(PixieInterface PRIVATE "-fPIC")

file(GLOB PIXIE_INTERFACE_PUBLIC_HEADERS include/*.h)
set_target_properties(PixieInterface PROPERTIES PUBLIC_HEADER "${PIXIE_INTERFACE_PUBLIC_HEADERS}")
install(TARGETS PixieInterface LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)