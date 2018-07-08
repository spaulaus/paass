# @author S. V. Paulauskas
option(PAASS_UTKSCAN_GAMMA_GATES "Gamma-Gamma gates in GeProcessor" OFF)
option(PAASS_UTKSCAN_ONLINE "Options for online scans" OFF)
option(PAASS_UTKSCAN_TREE_DEBUG "Debugging info for TreeCorrelator" OFF)
option(PAASS_UTKSCAN_VERBOSE "Make Scan More Verbose" OFF)

mark_as_advanced(PAASS_UTKSCAN_GAMMA_GATES PAASS_UTKSCAN_ONLINE PAASS_UTKSCAN_TREE_DEBUG PAASS_UTKSCAN_VERBOSE)

# newreadout is needed to account for a change to pixie16 readout
# structure change on 03/20/08. Is is REQUIRED!!
# @TODO : Need to determine if this is still required by the scan code.
add_definitions(-D newreadout)

#utkscan will have Gamma-Gamma gating in the CloverProcessor and GammaScintProcessor
if (PAASS_UTKSCAN_GAMMA_GATES)
    add_definitions(-DGGATES)
endif (PAASS_UTKSCAN_GAMMA_GATES)

#utkscan will be streamlined for online processing
if (PAASS_UTKSCAN_ONLINE)
    add_definitions(-DONLINE)
endif (PAASS_UTKSCAN_ONLINE)

#utkscan will have debugging for the TreeCorrelator
if (PAASS_UTKSCAN_TREE_DEBUG)
    add_definitions(-DTREE_DEBUG)
endif (PAASS_UTKSCAN_TREE_DEBUG)

#utkscan will be more verbose in its output
if (PAASS_UTKSCAN_VERBOSE)
    add_definitions(-DVERBOSE)
endif (PAASS_UTKSCAN_VERBOSE)

#------------------------------------------------------------------------------

include_directories(analyzers/include core/include experiment/include processors/include)
add_subdirectory(analyzers)
add_subdirectory(core)
add_subdirectory(experiment)
add_subdirectory(processors)

#added by T.T. King for Vector Root Libs
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_SKIP_INSTALL_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

ROOT_GENERATE_DICTIONARY(SysRootStruc ProcessorRootStruc.hpp LINKDEF processors/include/SysRootLinkDef.hpp )
add_library(SysRootStrucLib SHARED SysRootStruc.cxx SysRootStruc)

#End T.T. King Additions
#------------------------------------------------------------------------------

if (NOT PAASS_USE_HRIBF)
    set(SCAN_NAME utkscan)
    add_executable(${SCAN_NAME}
            $<TARGET_OBJECTS:UtkscanMainObjects>
            $<TARGET_OBJECTS:UtkscanCoreObjects>
            $<TARGET_OBJECTS:UtkscanAnalyzerObjects>
            $<TARGET_OBJECTS:UtkscanProcessorObjects>
            $<TARGET_OBJECTS:UtkscanExperimentObjects>
            SysRootStruc.cxx)
else (PAASS_USE_HRIBF)
    set(SCAN_NAME utkscanor)
    add_executable(${SCAN_NAME}
            $<TARGET_OBJECTS:UtkscanMainObjects>
            $<TARGET_OBJECTS:UtkscanCoreObjects>
            $<TARGET_OBJECTS:UtkscanAnalyzerObjects>
            $<TARGET_OBJECTS:UtkscanProcessorObjects>
            $<TARGET_OBJECTS:UtkscanExperimentObjects>
            $<TARGET_OBJECTS:ScanorObjects>)
    target_link_libraries(utkscanor ${HRIBF_LIBRARIES})
endif (NOT PAASS_USE_HRIBF)

target_link_libraries(${SCAN_NAME} ${LIBS} PaassScanStatic ResourceStatic PaassCoreStatic PugixmlStatic
        PaassResourceStatic ${GSL_LIBRARIES} ${ROOT_LIBRARIES})

#------------------------------------------------------------------------------

install(TARGETS ${SCAN_NAME} DESTINATION bin)
install(DIRECTORY share/utkscan DESTINATION share)
install(TARGETS SysRootStrucLib DESTINATION lib)

install(FILES ${CMAKE_SOURCE_DIR}/Analysis/Utkscan/processors/include/ProcessorRootStruc.hpp DESTINATION include/)
install(FILES ${CMAKE_SOURCE_DIR}/Analysis/Utkscan/processors/include/GSaddback.hpp DESTINATION include/)
#Install the ROOT 6 PCM.
if (${ROOT_VERSION} VERSION_GREATER "6.0")
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/SysRootStruc_rdict.pcm DESTINATION lib/)
endif (${ROOT_VERSION} VERSION_GREATER "6.0")
