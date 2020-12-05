add_library(PaassScan SHARED source/ScanInterface.cpp source/Unpacker.cpp source/XiaData.cpp
        source/XiaListModeDataDecoder.cpp source/XiaListModeDataEncoder.cpp source/XiaListModeDataMask.cpp)

if (XIA_FOUND)
    target_sources(PaassScan source/StatsData.cpp)
endif(XIA_FOUND)

target_include_directories(PaassScan PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include ${XIA_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include)
target_link_libraries(PaassScan PaassResources PaassCore Pugixml-1.11.1 ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})

file(GLOB PAASS_SCAN_PUBLIC_HEADERS include/*.hpp)
set_target_properties(PaassScan PROPERTIES PUBLIC_HEADER "${PAASS_SCAN_PUBLIC_HEADERS}")
install(TARGETS PaassScan LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
