add_library(Pugixml-1.11.1 SHARED pugixml/source/pugixml.cpp)
target_include_directories(Pugixml-1.11.1 PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include)
install(TARGETS Pugixml-1.11.1 DESTINATION lib)
