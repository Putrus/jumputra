cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game_physics
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Game physics project"
   )

set(HEADERS
   inc/Body.hpp
   inc/Entity.hpp
   inc/Physics.hpp
   inc/Properties.hpp
   inc/Segment.hpp
   inc/Wind.hpp
   )
set(SOURCES
   src/Body.cpp
   src/Entity.cpp
   src/Physics.cpp
   src/Segment.cpp
   src/Wind.cpp
   )

add_library(jp_game_physics STATIC ${HEADERS} ${SOURCES})