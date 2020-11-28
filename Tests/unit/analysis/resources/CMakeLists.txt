target_sources(tests PUBLIC
        ${PROJECT_SOURCE_DIR}/Tests/unit/analysis/resources/test_ChannelConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/ChannelConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/source/TimingConfiguration.cpp)
target_include_directories(tests PUBLIC
        ${PROJECT_SOURCE_DIR}/Analysis/Resources/include
        ${PROJECT_SOURCE_DIR}/Resources/include)
