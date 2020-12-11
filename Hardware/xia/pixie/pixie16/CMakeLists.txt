add_library(PixieInterface SHARED source/XiaData.cpp source/XiaListModeDataDecoder.cpp source/XiaListModeDataEncoder.cpp
        source/XiaListModeDataMask.cpp)

if (PAASS_BUILD_ACQ)
    find_package(PLX REQUIRED)
    find_package(XIA REQUIRED)

    include(GenerateDAQConfig)
    GENERATE_DAQ_CONFIG()

    target_sources(PixieInterface PUBLIC source/EmulatedInterface.cpp source/PixieInterface.cpp
            source/PixieSupport.cpp)

    target_link_directories(PixieInterface PUBLIC ${XIA_LIBRARY_DIR} ${PLX_LIBRARY_DIR})
    target_link_libraries(PixieInterface PaassInterfaces ${XIA_LIBRARIES} ${PLX_LIBRARIES})
    target_compile_options(PixieInterface PRIVATE "-DPLX_LINUX")
ENDIF (PAASS_BUILD_ACQ)

target_include_directories(PixieInterface PUBLIC include ${PROJECT_SOURCE_DIR}/Core/include ${XIA_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${PROJECT_SOURCE_DIR}/Resources/include ${ROOT_INCLUDE_DIR})
target_link_libraries(PixieInterface PaassCore PaassResources Pugixml-1.11.1)

file(GLOB PIXIE_INTERFACE_PUBLIC_HEADERS include/*.h)
set_target_properties(PixieInterface PROPERTIES PUBLIC_HEADER "${PIXIE_INTERFACE_PUBLIC_HEADERS}")
install(TARGETS PixieInterface LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

