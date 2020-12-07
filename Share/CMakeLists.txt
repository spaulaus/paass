# @author S.V. Paulauskas

#Configure and install the module file
configure_file("modulefiles/pixieSuite" pixieSuite @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pixieSuite DESTINATION usr/share/modules/modulefiles/)

#Configure and install the systemd service file 
configure_file("plx/systemd/plx.service" plx.service @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plx.service DESTINATION etc/systemd/system/)

#Configure and install the init.d script to load the plx drivers
configure_file("plx/init.d/plxload" plxload @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plxload DESTINATION etc/init.d/)

#Configure and install the init.d script to unload the plx drivers
configure_file("plx/systemd/plx.service" plxunload @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plxunload DESTINATION etc/init.d/)
