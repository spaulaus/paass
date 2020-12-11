set(SETUP_UTILS adjust_offsets find_tau copy_params pread pwrite pmread pmwrite
        rate boot trace get_traces csr_test toggle set_standard set_pileups_only
        set_pileups_reject set_hybrid)

foreach (UTIL ${SETUP_UTILS})
    add_executable(${UTIL} source/${UTIL}.cpp)
    target_compile_definitions(${UTIL} PUBLIC "-DPLX_LINUX")
    target_link_libraries(${UTIL} PaassInterfaces PixieInterface)
    target_include_directories(${UTIL} PUBLIC include ${PROJECT_SOURCE_DIR}/Hardware/Interface/include
            ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include)
endforeach (UTIL)

install(TARGETS ${SETUP_UTILS} DESTINATION bin)

add_executable(paramScan source/paramScan.cpp)
target_include_directories(paramScan PUBLIC include ${PROJECT_SOURCE_DIR}/Hardware/Interface/include
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include ${ROOT_INCLUDE_DIR})
target_link_libraries(paramScan PaassInterfaces PixieInterface MCALibrary ${ROOT_LIBRARIES} Spectrum)
install(TARGETS paramScan DESTINATION bin)

install(DIRECTORY share/traces DESTINATION share)
install(PROGRAMS bin/viewBaseline.sh DESTINATION bin RENAME viewBaseline)
