#@author S. V. Paulauskas
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/include)

# TODO: This is more of an integration test than a strict unit test. We're not going to fight with it until we decide what to do with mocks.
#target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/utkscan/core/test_DetectorSummary.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/DetectorSummary.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/DetectorLibrary.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/MapNodeXmlParser.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/TreeCorrelator.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/TreeCorrelatorXmlParser.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/WalkCorrector.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/Calibrator.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/PlaceBuilder.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/Places.cpp
#        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/RawEvent.cpp
#)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/utkscan/core/test_RootHandler.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/RootHandler.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/utkscan/core/test_WalkCorrector.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/WalkCorrector.cpp)