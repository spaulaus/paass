if (PAASS_BUILD_UTKSCAN)
    #------------------------------------------------------------------------------
    set(UTKSCAN_NAME utkscan)
    add_executable(${UTKSCAN_NAME} core/source/utkscan.cpp)
    #------------------------------------------------------------------------------

    if (PAASS_UTKSCAN_GAMMA_GATES)
        target_compile_definitions(${UTKSCAN_NAME} PUBLIC -DGGATES)
    endif (PAASS_UTKSCAN_GAMMA_GATES)

    if (PAASS_UTKSCAN_ONLINE)
        target_compile_definitions(${UTKSCAN_NAME} PUBLIC -DONLINE)
    endif (PAASS_UTKSCAN_ONLINE)

    if (PAASS_UTKSCAN_TREE_DEBUG)
        target_compile_definitions(${UTKSCAN_NAME} PUBLIC -DTREE_DEBUG)
    endif (PAASS_UTKSCAN_TREE_DEBUG)

    if (PAASS_UTKSCAN_VERBOSE)
        target_compile_definitions(${UTKSCAN_NAME} PUBLIC -DVERBOSE)
    endif (PAASS_UTKSCAN_VERBOSE)

    #------------------------------------------------------------------------------

    add_subdirectory(analyzers)
    add_subdirectory(core)
    add_subdirectory(experiment)
    add_subdirectory(processors)

    #------------------------------------------------------------------------------

    ROOT_GENERATE_DICTIONARY(PaassRootStruct core/include/PaassRootStruct.hpp LINKDEF core/include/PaassRootLinkDef.hpp)
    add_library(PaassRootStruct SHARED ${CMAKE_CURRENT_BINARY_DIR}/PaassRootStruct.cxx PaassRootStruct)
    target_link_libraries(PaassRootStruct ${ROOT_LIBRARIES})
    target_include_directories(PaassRootStruct PUBLIC ${ROOT_INCLUDE_DIR})

    #------------------------------------------------------------------------------

    target_link_libraries(${UTKSCAN_NAME} PaassScan AnalysisResources PaassCore Pugixml-1.11.1
            PaassResources ${GSL_LIBRARIES} ${ROOT_LIBRARIES} PaassRootStruct)

    target_include_directories(${UTKSCAN_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Analysis/Resources/include
            ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include
            ${PROJECT_SOURCE_DIR}/Resources/include ${PROJECT_SOURCE_DIR}/Core/include ${ROOT_INCLUDE_DIR}
            ${GSL_INCLUDE_DIR})

    #------------------------------------------------------------------------------

    install(TARGETS ${UTKSCAN_NAME} DESTINATION bin)
    install(TARGETS PaassRootStruct DESTINATION lib)
    install(DIRECTORY share/utkscan DESTINATION share)

    install(FILES core/include/PaassRootStruct.hpp DESTINATION include/)
    install(FILES processors/include/GSaddback.hpp DESTINATION include/)
    if (${ROOT_VERSION} VERSION_GREATER "6.0")
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PaassRootStruct_rdict.pcm DESTINATION lib/)
    endif (${ROOT_VERSION} VERSION_GREATER "6.0")
endif (PAASS_BUILD_UTKSCAN)
