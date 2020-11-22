# @author S. V. Paulauskas

add_executable(unittest-XiaListModeDataDecoder unittest-XiaListModeDataDecoder.cpp ../source/XiaData.cpp
        ../source/XiaListModeDataDecoder.cpp ../source/XiaListModeDataMask.cpp)
target_link_libraries(unittest-XiaListModeDataDecoder UnitTest++ ${LIBS})
add_test(XiaListModeDataDecoder unittest-XiaListModeDataDecoder)

add_executable(unittest-XiaListModeDataEncoder unittest-XiaListModeDataEncoder.cpp ../source/XiaData.cpp
        ../source/XiaListModeDataEncoder.cpp ../source/XiaListModeDataMask.cpp)
target_link_libraries(unittest-XiaListModeDataEncoder UnitTest++ ${LIBS})
add_test(XiaListModeDataEncoder unittest-XiaListModeDataEncoder)

add_executable(unittest-XiaListModeDataMask unittest-XiaListModeDataMask.cpp ../source/XiaData.cpp
        ../source/XiaListModeDataMask.cpp)
target_link_libraries(unittest-XiaListModeDataMask UnitTest++ ${LIBS})
add_test(XiaListModeDataMask unittest-XiaListModeDataMask)

add_executable(unittest-XiaData unittest-XiaData.cpp ../source/XiaData.cpp)
target_link_libraries(unittest-XiaData UnitTest++ ${LIBS})
add_test(XiaListModeData unittest-XiaData)

add_executable(unittest-Trace unittest-Trace.cpp)
target_link_libraries(unittest-Trace UnitTest++ ${LIBS})
add_test(Trace unittest-Trace)