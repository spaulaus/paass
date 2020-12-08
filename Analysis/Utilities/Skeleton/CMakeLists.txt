add_executable(skeleton source/Skeleton.cpp source/SkeletonUnpacker.cpp source/SkeletonInterface.cpp)
target_include_directories(skeleton PUBLIC include ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${PROJECT_SOURCE_DIR}/Resources/include
        ${ROOT_INCLUDE_DIR})
target_link_libraries(skeleton PaassScan Pugixml-1.11.1 PaassResources ${ROOT_LIBRARIES})

if (PAASS_USE_HRIBF)
    target_link_libraries(skeleton PaassScanor ${HRIBF_LIBRARIES})
endif (PAASS_USE_HRIBF)

install(TARGETS skeleton DESTINATION bin)
