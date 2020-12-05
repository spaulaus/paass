add_library(Pugixml-1.11.1 SHARED source/pugixml.cpp)
target_include_directories(Pugixml-1.11.1 PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include)

file(GLOB PUGIXML_PUBLIC_HEADERS include/*.hpp)
set_target_properties(Pugixml-1.11.1 PROPERTIES PUBLIC_HEADER "${PUGIXML_PUBLIC_HEADERS}")
install(TARGETS Pugixml-1.11.1 LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
