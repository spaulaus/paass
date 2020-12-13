add_library(DataFormats SHARED source/hribf_buffers.cpp)
target_link_libraries(DataFormats PollServer)
target_include_directories(DataFormats PUBLIC include ${PROJECT_SOURCE_DIR}/Acquisition/Poll/include)

file(GLOB DATA_FORMATS_PUBLIC_HEADERS include/*.h)
set_target_properties(DataFormats PROPERTIES PUBLIC_HEADER "${DATA_FORMATS_PUBLIC_HEADERS}")
install(TARGETS DataFormats LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
