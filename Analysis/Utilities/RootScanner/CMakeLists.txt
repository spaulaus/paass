root_generate_dictionary(HistScannerDictionary include/HistScannerChanData.hpp LINKDEF include/HistScannerLinkDef.h)
add_executable(rootscan source/HistUnpacker.cpp source/HistScanner.cpp source/HistScannerChanData.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/HistScannerDictionary.cxx source/hist.cpp)
target_include_directories(rootscan PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include ${PROJECT_SOURCE_DIR}/Analysis/Resources/include
        ${ROOT_INCLUDE_DIR})
target_link_libraries(rootscan PaassScan AnalysisResources Pugixml-1.11.1 PaassResources ${ROOT_LIBRARIES} -lTreePlayer)
install(TARGETS rootscan DESTINATION bin)