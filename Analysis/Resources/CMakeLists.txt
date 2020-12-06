add_library(AnalysisResources SHARED source/ChannelConfiguration.cpp source/CrystalBallFunction.cpp
        source/CsiFunction.cpp source/EmCalTimingFunction.cpp source/GslFitter.cpp source/PolynomialCfd.cpp
        source/RootFitter.cpp source/SiPmtFastTimingFunction.cpp source/TimingConfiguration.cpp source/TraceFilter.cpp
        source/TraditionalCfd.cpp source/VandleTimingFunction.cpp source/XiaCfd.cpp)

if (${GSL_VERSION} LESS 2.0)
    target_compile_definitions(AnalysisResource "-DGSL_VERSION_ONE")
endif (${GSL_VERSION} LESS 2.0)

target_include_directories(AnalysisResources PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include ${GSL_INCLUDE_DIRS})
target_link_libraries(AnalysisResources PaassResources ${ROOT_LIBRARIES} ${GSL_LIBRARIES})

file(GLOB ANALYSIS_RESOURCES_PUBLIC_HEADERS include/*.hpp)
set_target_properties(AnalysisResources PROPERTIES PUBLIC_HEADER "${ANALYSIS_RESOURCES_PUBLIC_HEADERS}")
install(TARGETS AnalysisResources LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)