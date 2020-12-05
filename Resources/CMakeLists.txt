message(STATUS "Building PaassResource library")
add_library(PaassResources SHARED source/Messenger.cpp source/Notebook.cpp source/RandomInterface.cpp
        source/XmlInterface.cpp source/XmlParser.cpp)

target_include_directories(PaassResources PUBLIC ${PROJECT_SOURCE_DIR}/Resources/include
        ${PROJECT_SOURCE_DIR}/ThirdParty/pugixml/include ${ROOT_INCLUDE_DIR})

if (ROOT_FOUND)
    if(ROOT_HAS_MINUIT2)
        add_definitions("-D ROOT_HAS_MINUIT2")
    endif(ROOT_HAS_MINUIT2)
    target_sources(PaassResources PUBLIC ${PROJECT_SOURCE_DIR}/Resources/source/RootInterface.cpp)
endif (ROOT_FOUND)

target_link_libraries(PaassResources Pugixml-1.11.1)
install(TARGETS PaassResources DESTINATION lib)

