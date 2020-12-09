#Configure and install the module file
configure_file("modulefiles/paass" paass @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/paass DESTINATION usr/share/modules/modulefiles/)

#Configure and install the systemd service file 
configure_file("broadcom/systemd/broadcom.service" broadcom.service @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/broadcom.service DESTINATION etc/systemd/system/)

#Configure and install the init.d script to load the plx drivers
configure_file("broadcom/init.d/plxload" plxload @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plxload DESTINATION etc/init.d/)

#Configure and install the init.d script to unload the plx drivers
configure_file("broadcom/init.d/plxunload" plxunload @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plxunload DESTINATION etc/init.d/)
