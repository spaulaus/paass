add_library(PaassInterfaces SHARED source/AcquisitionConfig.cpp source/AcquisitionInterface.cpp)
target_include_directories(PaassInterfaces PUBLIC include ${PROJECT_SOURCE_DIR}/Terminal/include ${XIA_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${PROJECT_SOURCE_DIR}/Resources/include ${ROOT_INCLUDE_DIR})
target_link_libraries(PaassInterfaces Terminal PaassResources Pugixml-1.11.1 ${XIA_LIBRARIES} ${PLX_LIBRARIES}
        ${ROOT_LIBRARIES})
target_compile_definitions(PaassInterfaces PUBLIC -DINSTALL_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")

file(GLOB PIXIE_INTERFACE_PUBLIC_HEADERS include/*.h)
set_target_properties(PaassInterfaces PROPERTIES PUBLIC_HEADER "${PIXIE_INTERFACE_PUBLIC_HEADERS}")
install(TARGETS PaassInterfaces LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)