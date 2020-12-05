add_definitions(-D INSTALL_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")
if (PAASS_BUILD_ACQ)
    add_subdirectory(Interface)
    add_subdirectory(MCA)
    add_subdirectory(Poll)
    add_subdirectory(Utilities/listener)
    add_subdirectory(Utilities/monitor)
    add_subdirectory(Utilities/send_alarm)
endif (PAASS_BUILD_ACQ)

add_subdirectory(set2root)

#add_subdirectory(Utilities/DataGenerator)
#add_subdirectory(Setup)
