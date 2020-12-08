add_library(PaassCore SHARED source/CTerminal.cpp source/Display.cpp source/hribf_buffers.cpp source/poll2_socket.cpp)
target_link_libraries(PaassCore ${CURSES_LIBRARIES})
target_include_directories(PaassCore PUBLIC include)

file(GLOB PAASS_CORE_PUBLIC_HEADERS include/*.h)
set_target_properties(PaassCore PROPERTIES PUBLIC_HEADER "${PAASS_CORE_PUBLIC_HEADERS}")
install(TARGETS PaassCore LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
