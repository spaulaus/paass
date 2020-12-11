add_executable(poll2 source/poll2.cpp source/poll2_core.cpp source/poll2_stats.cpp)
target_include_directories(poll2 PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Hardware/Interface/include ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/args/)
target_link_libraries(poll2 PaassInterfaces PixieInterface MCALibrary ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS poll2 DESTINATION bin)
