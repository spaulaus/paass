# @author S. V. Paulauskas

target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/scan_libraries/test_Trace.cpp)

#target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/scan_libraries/test_XiaData.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/source/XiaData.cpp)
#
#target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/scan_libraries/test_XiaListModeDataDecoder.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/source/XiaListModeDataDecoder.cpp)
#
#target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/scan_libraries/test_XiaListModeDataEncoder.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/source/XiaListModeDataEncoder.cpp)
#
#target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/scan_libraries/test_XiaListModeDataMask.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/source/XiaListModeDataMask.cpp)