option(PAASS_BUILD_UTKSCAN "Build utkscan" ON)
if (PAASS_BUILD_UTKSCAN)
    #------------------------------------------------------------------------------
    if (NOT PAASS_USE_HRIBF)
        set(UTKSCAN_NAME utkscan)
        add_executable(${UTKSCAN_NAME} core/source/utkscan.cpp)
    else (PAASS_USE_HRIBF)
        set(UTKSCAN_NAME utkscanor)
        add_executable(${UTKSCAN_NAME} core/source/utkscanor.cpp)
    endif (NOT PAASS_USE_HRIBF)

    #------------------------------------------------------------------------------

    option(PAASS_UTKSCAN_GAMMA_GATES "Gamma-Gamma gates in GeProcessor" OFF)
    option(PAASS_UTKSCAN_ONLINE "Options for online scans" OFF)
    option(PAASS_UTKSCAN_TREE_DEBUG "Debugging info for TreeCorrelator" OFF)
    option(PAASS_UTKSCAN_VERBOSE "Make Scan More Verbose" OFF)

    mark_as_advanced(PAASS_UTKSCAN_GAMMA_GATES PAASS_UTKSCAN_ONLINE PAASS_UTKSCAN_TREE_DEBUG PAASS_UTKSCAN_VERBOSE)

    # newreadout is needed to account for a change to pixie16 readout
    # structure change on 03/20/08. Is is REQUIRED!!
    # @TODO : Need to determine if this is still required by the scan code.
    target_compile_definitions(${UTKSCAN_NAME} PUBLIC -Dnewreadout)

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

    if (PAASS_USE_HRIBF)
        target_link_libraries(${UTKSCAN_NAME} ${HRIBF_LIBRARIES})
        target_include_directories(${UTKSCAN_NAME} ${PROJECT_SOURCE_DIR}/Analysis/Scanor/include)
    endif (PAASS_USE_HRIBF)

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
