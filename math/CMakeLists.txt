cmake_minimum_required(VERSION 3.6..3.28)

project(jp_math
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Math library for jumputra project"
   )

set(HEADERS
   inc/Math.hpp
   inc/Rect.hpp
   inc/Segment.hpp
   inc/Vector2.hpp
   )
set(SOURCES
   src/Math.cpp
   )

add_library(jp_math STATIC ${HEADERS} ${SOURCES})