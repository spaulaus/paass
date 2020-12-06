add_executable(scope source/scope.cpp source/ScopeUnpacker.cpp source/ScopeScanner.cpp)
target_link_libraries(scope PaassResources PaassScan Pugixml-1.11.1 AnalysisResources ${ROOT_LIBRARIES} ${GSL_LIBRARIES})
target_include_directories(scope PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${PROJECT_SOURCE_DIR}/Analysis/Resources/include
        ${ROOT_INCLUDE_DIR} ${GSL_INCLUDE_DIRS})

if (PAASS_USE_HRIBF)
    target_link_libraries(scope PaassScanor ${HRIBF_LIBRARIES})
endif (PAASS_USE_HRIBF)

install(TARGETS scope DESTINATION bin)