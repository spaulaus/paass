if (PAASS_BUILD_ANALYSIS)
    add_subdirectory(Resources)
    add_subdirectory(ScanLibraries)
    add_subdirectory(Utilities)
    add_subdirectory(Utkscan)
endif (PAASS_BUILD_ANALYSIS)

#option(PAASS_USE_HRIBF "Use HRIBF library for scan base." OFF)
#if (PAASS_USE_HRIBF)
#    #Find HRIBF Libraries
#    find_package(HRIBF REQUIRED)
#    add_definitions("-D USE_HRIBF")
#
#    enable_language(Fortran)
#
#    #If we are using HRIBF interface we need to include the ScanorInterface header for the following code.
#    include_directories(Scanor/include)
#    add_subdirectory(Scanor)
#endif (PAASS_USE_HRIBF)

