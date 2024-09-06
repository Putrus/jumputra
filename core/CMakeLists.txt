cmake_minimum_required(VERSION 3.6..3.28)

project(jp_core
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra core"
)

set(HEADERS
   inc/Jsonable.hpp
   inc/Logger.hpp
   inc/Random.hpp
   inc/String.hpp
   )

set(SOURCES
   src/Jsonable.cpp
   src/Logger.cpp
   src/Random.cpp
   src/String.cpp
   )

add_library(jp_core STATIC ${HEADERS} ${SOURCES})
