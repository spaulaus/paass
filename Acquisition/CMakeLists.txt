add_subdirectory(Utilities/set2root)
add_subdirectory(Setup)

if (PAASS_BUILD_ACQ)
    add_subdirectory(MCA)
    add_subdirectory(Poll)
    add_subdirectory(Utilities/listener)
    add_subdirectory(Utilities/monitor)
    add_subdirectory(Utilities/send_alarm)
    add_subdirectory(Utilities/param_scan)
endif (PAASS_BUILD_ACQ)

