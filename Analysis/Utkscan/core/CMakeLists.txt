target_sources(${UTKSCAN_NAME} PUBLIC
        source/BarBuilder.cpp
        source/Calibrator.cpp
        source/Correlator.cpp
        source/DetectorDriver.cpp
        source/DetectorDriverXmlParser.cpp
        source/DetectorLibrary.cpp
        source/DetectorSummary.cpp
        source/Globals.cpp
        source/GlobalsXmlParser.cpp
        source/MapNodeXmlParser.cpp
        source/Places.cpp
        source/PlaceBuilder.cpp
        source/Plots.cpp
        source/PlotsRegister.cpp
        source/RawEvent.cpp
        source/RootHandler.cpp
        source/TimingCalibrator.cpp
        source/TimingMapBuilder.cpp
        source/TreeCorrelator.cpp
        source/TreeCorrelatorXmlParser.cpp
        source/UtkScanInterface.cpp
        source/UtkUnpacker.cpp
        source/WalkCorrector.cpp)
target_include_directories(${UTKSCAN_NAME} PUBLIC include)