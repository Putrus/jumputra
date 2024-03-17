cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game_physics
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Game physics project"
   )

set(HEADERS
   inc/Entity.hpp
   inc/Physics.hpp
   inc/Properties.hpp
   inc/Segment.hpp
   )
set(SOURCES
   src/Entity.cpp
   src/Physics.cpp
   src/Segment.cpp
   )

add_library(jp_game_physics STATIC ${HEADERS} ${SOURCES})