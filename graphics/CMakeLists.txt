cmake_minimum_required(VERSION 3.6..3.28)

project(jp_graphics
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra graphics"
)

set(HEADERS
   inc/Character.hpp
   inc/Goal.hpp
   inc/Properties.hpp
   inc/ResourceManager.hpp
   inc/Resources.hpp
   inc/Segment.hpp
   inc/Wind.hpp
   inc/Window.hpp
   )

set(SOURCES
   src/Character.cpp
   src/Goal.cpp
   src/Properties.cpp
   src/Resources.cpp
   src/Segment.cpp
   src/Wind.cpp
   src/Window.cpp
   )

find_package(SFML COMPONENTS graphics window audio system CONFIG REQUIRED)

add_library(jp_graphics STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_graphics PUBLIC jp_core sfml-graphics sfml-window sfml-audio sfml-system)
