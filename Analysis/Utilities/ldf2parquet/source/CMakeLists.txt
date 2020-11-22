# @authors S. V. Paulauskas
add_executable(ldf2parquet ldf2parquet.cpp ldf2ParquetInterface.cpp ldf2ParquetUnpacker.cpp)
target_link_libraries(ldf2parquet PaassScanStatic PugixmlStatic PaassResourceStatic parquet)
install(TARGETS ldf2parquet DESTINATION bin)
