cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game_physics
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Game physics project"
   )

set(HEADERS
   inc/Body.hpp
   inc/BodyUpdater.hpp
   inc/DiagonalSegment.hpp
   inc/Entity.hpp
   inc/HorizontalSegment.hpp
   inc/Physics.hpp
   inc/Properties.hpp
   inc/Segment.hpp
   inc/VerticalSegment.hpp
   inc/Wind.hpp
   inc/WindUpdater.hpp
   )
set(SOURCES
   src/Body.cpp
   src/BodyUpdater.cpp
   src/DiagonalSegment.cpp
   src/Entity.cpp
   src/HorizontalSegment.cpp
   src/Physics.cpp
   src/Segment.cpp
   src/VerticalSegment.cpp
   src/Wind.cpp
   src/WindUpdater.cpp
   )

add_library(jp_game_physics STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_game_physics PRIVATE jp_math)