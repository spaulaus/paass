add_library(PollServer SHARED source/poll2_socket.cpp)
target_include_directories(PollServer PUBLIC include)
install(TARGETS PollServer DESTINATION lib)

add_executable(poll2 source/poll2.cpp source/poll2_core.cpp source/poll2_stats.cpp)
target_include_directories(poll2 PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Hardware/Interface/include ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/args/
        ${PROJECT_SOURCE_DIR}/DataFormats/hribf/include)
target_link_libraries(poll2 PollServer PaassInterfaces PixieInterface MCALibrary DataFormats ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS poll2 DESTINATION bin)

