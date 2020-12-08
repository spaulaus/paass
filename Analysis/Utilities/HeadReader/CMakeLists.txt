add_executable(headReader source/headReader.cpp)
target_include_directories(headReader PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include
        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include ${PROJECT_SOURCE_DIR}/Resources/include)
target_link_libraries(headReader PaassScan Pugixml-1.11.1 PaassResources ${ROOT_LIBRARIES})
install(TARGETS headReader DESTINATION bin)