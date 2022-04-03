add_executable(list_mode_converter
        source/list_mode_converter.cpp
        source/list_mode_converter_interface.cpp
        source/list_mode_converter_unpacker.cpp)
target_include_directories(list_mode_converter PUBLIC include
        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include
        ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Core/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include
        ${ROOT_INCLUDE_DIR}
        ${PIXIESDK_INCLUDE_DIR})
target_link_directories(list_mode_converter PUBLIC ${PIXIESDK_LIBRARY_DIR})
target_link_libraries(list_mode_converter PaassScan Pugixml-1.11.1 PaassResources PixieData)
install(TARGETS list_mode_converter DESTINATION bin)