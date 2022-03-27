add_executable(ldf2parquet source/ldf2parquet.cpp source/ldf2ParquetInterface.cpp source/ldf2ParquetUnpacker.cpp)
target_include_directories(ldf2parquet PUBLIC include
        ${PROJECT_SOURCE_DIR}/Analysis/ScanLibraries/include
        ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/Core/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include
        ${ROOT_INCLUDE_DIR}
        ${PIXIESDK_INCLUDE_DIR})
target_link_directories(ldf2parquet PUBLIC ${PIXIESDK_LIBRARY_DIR})
target_link_libraries(ldf2parquet PaassScan Pugixml-1.11.1 PaassResources PixieData ${ROOT_LIBRARIES} parquet)
install(TARGETS ldf2parquet DESTINATION bin)