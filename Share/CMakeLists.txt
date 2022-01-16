#Configure and install the module file
configure_file("modulefiles/paass" paass @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/paass DESTINATION usr/share/modules/modulefiles/)

#Configure and install the systemd service file 
configure_file("plx/systemd/plx.service" plx.service @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plx.service DESTINATION etc/systemd/system/)
