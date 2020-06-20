# @authors S. V. Paulauskas
add_executable(Ldf2Parquet Ldf2Parquet.cpp Ldf2ParquetUnpacker.cpp Ldf2ParquetInterface.cpp)
target_link_libraries(Ldf2Parquet PaassScanStatic PugixmlStatic PaassResourceStatic)
install(TARGETS Ldf2Parquet DESTINATION bin)
