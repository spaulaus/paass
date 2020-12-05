# @authors S. V. Paulauskas
set(PROCESSOR_SOURCES
        BetaScintProcessor.cpp
        DoubleBetaProcessor.cpp
        CloverCalibProcessor.cpp
        CloverFragProcessor.cpp
        CloverProcessor.cpp
        DssdProcessor.cpp
        EventProcessor.cpp
        ExtTSSenderProcessor.cpp
        GammaScintProcessor.cpp
        GammaScintFragProcessor.cpp
        GeProcessor.cpp
        Hen3Processor.cpp
        ImplantSsdProcessor.cpp
        IonChamberProcessor.cpp
        LiquidScintProcessor.cpp
        LitePositionProcessor.cpp
        LogicProcessor.cpp
        McpProcessor.cpp
        NeutronScintProcessor.cpp
        PositionProcessor.cpp
        PspmtProcessor.cpp
        RootDevProcessor.cpp
        SingleBetaProcessor.cpp
        TeenyVandleProcessor.cpp
        TemplateProcessor.cpp
        VandleProcessor.cpp
        )

add_library(UtkscanProcessorObjects OBJECT ${PROCESSOR_SOURCES})
