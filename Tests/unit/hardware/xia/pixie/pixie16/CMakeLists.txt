target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/include)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/hardware/xia/pixie/pixie16/test_XiaData.cpp
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/source/XiaData.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/hardware/xia/pixie/pixie16/test_XiaListModeDataDecoder.cpp
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/source/XiaListModeDataDecoder.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/hardware/xia/pixie/pixie16/test_XiaListModeDataEncoder.cpp
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/source/XiaListModeDataEncoder.cpp)

target_sources(tests PUBLIC ${PROJECT_SOURCE_DIR}/Tests/unit/hardware/xia/pixie/pixie16/test_XiaListModeDataMask.cpp
        ${PROJECT_SOURCE_DIR}/Hardware/xia/pixie/pixie16/source/XiaListModeDataMask.cpp)