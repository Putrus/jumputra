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

find_package(nlohmann_json REQUIRED)

add_library(jp_core STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_core PUBLIC nlohmann_json::nlohmann_json)