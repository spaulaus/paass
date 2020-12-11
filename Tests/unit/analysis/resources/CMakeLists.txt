target_include_directories(tests PUBLIC
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/include
        ${PROJECT_SOURCE_DIR}/Resources/include)
target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/TimingConfiguration.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_ChannelConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/ChannelConfiguration.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_GslFitter.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/GslFitter.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_PolynomialCfd.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/PolynomialCfd.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_TraditionalCfd.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/TraditionalCfd.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_XiaCfd.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/XiaCfd.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_RootFitter.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/RootFitter.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/VandleTimingFunction.cpp)
