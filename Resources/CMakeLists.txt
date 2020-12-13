add_library(PaassResources SHARED source/CerrDirector.cpp source/Messenger.cpp source/Notebook.cpp
        source/RandomInterface.cpp source/RootInterface.cpp source/Utility.cpp source/XmlInterface.cpp
        source/XmlParser.cpp)

if(ROOT_HAS_MINUIT2)
    add_definitions("-D ROOT_HAS_MINUIT2")
endif(ROOT_HAS_MINUIT2)

target_include_directories(PaassResources PUBLIC ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${ROOT_INCLUDE_DIR})

target_link_libraries(PaassResources Pugixml-1.11.1 ${ROOT_LIBRARIES})

file(GLOB PAASS_RESOURCES_PUBLIC_HEADERS include/*.hpp)
set_target_properties(PaassResources PROPERTIES PUBLIC_HEADER "${PAASS_RESOURCES_PUBLIC_HEADERS}")
install(TARGETS PaassResources LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
