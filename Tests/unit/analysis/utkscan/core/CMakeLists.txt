#@author S. V. Paulauskas
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/include)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/utkscan/core/test_RootHandler.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/RootHandler.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/utkscan/core/test_WalkCorrector.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Utkscan/core/source/WalkCorrector.cpp)