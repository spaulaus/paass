add_definitions(-D INSTALL_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")

add_subdirectory(Utilities/set2root)
add_subdirectory(Setup)
#TODO: We need to revist where this guy lives as he's dependent on the scan libraries. Maybe should live there??
#add_subdirectory(Utilities/DataGenerator)

if (PAASS_BUILD_ACQ)
    find_package(PLX REQUIRED)
    find_package(XIA REQUIRED)
    XIA_CONFIG()

    add_subdirectory(Interface)
    add_subdirectory(MCA)
    add_subdirectory(Poll)
    add_subdirectory(Utilities/listener)
    add_subdirectory(Utilities/monitor)
    add_subdirectory(Utilities/send_alarm)
endif (PAASS_BUILD_ACQ)

