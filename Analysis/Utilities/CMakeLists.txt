# @author S. V. Paulauskas


if(PAASS_BUILD_EVENT_READER)
    add_subdirectory(EventReader)
endif(PAASS_BUILD_EVENT_READER)

if(PAASS_BUILD_HEAD_READER)
    add_subdirectory(HeadReader)
endif(PAASS_BUILD_HEAD_READER)

if(PAASS_BUILD_HEX_READER)
    add_subdirectory(HexReader)
endif(PAASS_BUILD_HEX_READER)

if (PAASS_BUILD_LDF2PARQUET)
    add_subdirectory(Ldf2Parquet)
endif(PAASS_BUILD_LDF2PARQUET)

if(PAASS_BUILD_ROOT_SCANNER)
    add_subdirectory(RootScanner)
endif(PAASS_BUILD_ROOT_SCANNER)

if(PAASS_BUILD_SCOPE)
    add_subdirectory(Scope)
endif(PAASS_BUILD_SCOPE)

if(PAASS_BUILD_SKELETON)
    add_subdirectory(Skeleton)
endif(PAASS_BUILD_SKELETON)
