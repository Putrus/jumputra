cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game_physics
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Game physics project"
   )

set(HEADERS
   inc/Physics.hpp
   inc/PhysicsProperties.hpp
   )
set(SOURCES
   src/Physics.cpp
   )

add_library(jp_game_physics STATIC ${HEADERS} ${SOURCES})