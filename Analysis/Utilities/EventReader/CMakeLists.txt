add_executable(eventReader source/eventReader.cpp source/EventReaderInterface.cpp source/EventReaderUnpacker.cpp)

if (PAASS_USE_HRIBF)
    target_sources(eventReader $<TARGET_OBJECTS:ScanorObjects>)
    target_link_libraries(eventReader ${HRIBF_LIBRARIES})
endif (PAASS_USE_HRIBF)

target_link_libraries(eventReader PaassScan ${ROOT_LIBRARIES})
target_include_directories(eventReader PUBLIC include ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include
        ${ROOT_INCLUDE_DIR})
install(TARGETS eventReader DESTINATION bin)
