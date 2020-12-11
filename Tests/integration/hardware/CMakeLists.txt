target_include_directories(tests PUBLIC BEFORE
        ${PROJECT_SOURCE_DIR}/Core/include
        ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Acquisition/Interface/include)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/integration/hardware/interface/test_AcquisitionConfig.cpp
        ${PROJECT_SOURCE_DIR}/Acquisition/Interface/source/AcquisitionConfig.cpp
        ${PROJECT_SOURCE_DIR}/Resources/source/XmlInterface.cpp
        ${PROJECT_SOURCE_DIR}/Resources/source/XmlParser.cpp)