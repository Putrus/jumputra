cmake_minimum_required(VERSION 3.6..3.28)

project(jp_math
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "jumputra math"
   )

set(HEADERS
   inc/Math.hpp
   inc/Rect.hpp
   inc/Segment.hpp
   inc/Vector2.hpp
   )
set(SOURCES)

add_library(jp_math STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_math PUBLIC jp_core)