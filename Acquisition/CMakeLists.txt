add_definitions(-D INSTALL_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")

add_subdirectory(Setup)
#TODO: We need to revist where this guy lives as he's dependent on the scan libraries. Maybe should live there??
#add_subdirectory(Utilities/DataGenerator)

if (PAASS_BUILD_ACQ)
    find_package(BroadcomAPI REQUIRED)
    find_package(PixieSDK REQUIRED)

    add_subdirectory(Interface)
    add_subdirectory(MCA)
    add_subdirectory(Poll)
    add_subdirectory(Utilities/listener)
    add_subdirectory(Utilities/monitor)
endif (PAASS_BUILD_ACQ)

