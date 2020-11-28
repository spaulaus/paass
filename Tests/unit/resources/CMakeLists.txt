# @author S.V. Paulauskas

target_sources(tests PUBLIC
        ${PROJECT_SOURCE_DIR}/Tests/unit/resources/test_HelperFunctions.cpp
        ${PROJECT_SOURCE_DIR}/Tests/unit/resources/test_StringManipulationFunctions.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Resources/include)
