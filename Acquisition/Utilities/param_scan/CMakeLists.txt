add_executable(paramScan source/paramScan.cpp)
target_include_directories(paramScan PUBLIC include ${PROJECT_SOURCE_DIR}/Hardware/Interface/include
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include ${ROOT_INCLUDE_DIR})
target_link_libraries(paramScan PaassInterfaces PixieInterface MCALibrary ${ROOT_LIBRARIES} Spectrum)
install(TARGETS paramScan DESTINATION bin)