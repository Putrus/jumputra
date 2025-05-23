cmake_minimum_required(VERSION 3.6)

project(jp_logic
VERSION 0.0.3
LANGUAGES CXX
DESCRIPTION "jumputra logic"
)

set(HEADERS
   inc/Character.hpp
   inc/DiagonalSegment.hpp
   inc/Engine.hpp
   inc/Entity.hpp
   inc/Goal.hpp
   inc/HorizontalSegment.hpp
   inc/Properties.hpp
   inc/Runnable.hpp
   inc/Segment.hpp
   inc/SegmentsConnector.hpp
   inc/Selectable.hpp
   inc/SelectionManager.hpp
   inc/Statistics.hpp
   inc/Updatable.hpp
   inc/VerticalSegment.hpp
   inc/Wind.hpp
   )

set(SOURCES
   src/Character.cpp
   src/DiagonalSegment.cpp
   src/Engine.cpp
   src/Entity.cpp
   src/Goal.cpp
   src/HorizontalSegment.cpp
   src/Properties.cpp
   src/Runnable.cpp
   src/Segment.cpp
   src/SegmentsConnector.cpp
   src/Selectable.cpp
   src/SelectionManager.cpp
   src/Statistics.cpp
   src/VerticalSegment.cpp
   src/Wind.cpp
   )

add_library(jp_logic STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_logic PUBLIC jp_core)