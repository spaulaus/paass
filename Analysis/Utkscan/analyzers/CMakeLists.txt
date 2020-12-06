target_sources(${UTKSCAN_NAME} PUBLIC
        source/CfdAnalyzer.cpp
        source/FittingAnalyzer.cpp
        source/TauAnalyzer.cpp
        source/TraceExtractor.cpp
        source/TraceFilterAnalyzer.cpp
        source/TraceAnalyzer.cpp
        source/WaaAnalyzer.cpp
        source/WaveformAnalyzer.cpp)
target_include_directories(${UTKSCAN_NAME} PUBLIC include)