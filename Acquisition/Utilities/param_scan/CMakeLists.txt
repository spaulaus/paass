add_executable(paramScan source/paramScan.cpp)
target_include_directories(paramScan PUBLIC include ${PROJECT_SOURCE_DIR}/Acquisition/Interface/include
        ${ROOT_INCLUDE_DIR})
target_link_libraries(paramScan PixieInterface MCALibrary ${ROOT_LIBRARIES} "-lSpectrum")
install(TARGETS paramScan DESTINATION bin)