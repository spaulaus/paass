# @author S.V. Paulauskas

add_executable(unittest-HelperFunctions unittest-HelperFunctions.cpp)
target_link_libraries(unittest-HelperFunctions UnitTest++)
add_test(HelperFunctions unittest-HelperFunctions)

add_executable(unittest-StringManipulationFunctions unittest-StringManipulationFunctions.cpp)
target_link_libraries(unittest-StringManipulationFunctions UnitTest++)
add_test(StringManipulationFunctions unittest-StringManipulationFunctions)
