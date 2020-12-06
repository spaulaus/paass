target_sources(${UTKSCAN_NAME} PUBLIC
        source/Anl1471Processor.cpp
        #source/Beta4Hen3Processor.cpp
        #source/CrosstalkProcessor.cpp
        #source/Dssd4SHEProcessor.cpp
        source/E11027Processor.cpp
        #source/Ge4Hen3Processor.cpp
        source/IS600Processor.cpp
        #source/LaBr3TestProcessor.cpp
        source/SheCorrelator.cpp
        source/TemplateExpProcessor.cpp
        source/TwoChanTimingProcessor.cpp
        source/VandleOrnl2012Processor.cpp
        #source/WalkVandleBetaProcessor.cpp
        )
target_include_directories(${UTKSCAN_NAME} PUBLIC include)