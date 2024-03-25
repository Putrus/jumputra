cmake_minimum_required(VERSION 3.6..3.28)

project(jp_graphic
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra graphic"
)

set(HEADERS
   inc/Properties.hpp
   inc/ResourceManager.hpp
   inc/Resources.hpp
   inc/Window.hpp
   )

set(SOURCES
   src/Resources.cpp
   src/Window.cpp
   )

add_library(jp_graphic STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_graphic PUBLIC sfml-graphics sfml-window sfml-audio sfml-system)
