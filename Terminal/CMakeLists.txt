add_library(TerminalObjLib OBJECT source/CTerminal.cpp source/Display.cpp source/Lock.cpp)

add_library(Terminal SHARED $<TARGET_OBJECTS:TerminalObjLib>)
target_link_libraries(Terminal PaassResources ${CURSES_LIBRARIES})
target_include_directories(Terminal PUBLIC include ${PROJECT_SOURCE_DIR}/Resources/include)

file(GLOB PAASS_CORE_PUBLIC_HEADERS include/*.h)
set_target_properties(Terminal PROPERTIES PUBLIC_HEADER "${PAASS_CORE_PUBLIC_HEADERS}")
install(TARGETS Terminal LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
