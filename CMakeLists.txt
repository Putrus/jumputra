cmake_minimum_required(VERSION 3.6..3.28)

project(jumputra
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Comparative Analysis of Metaheuristics, Machine Learning, and Human in a Platform Game"
   )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/UpdateSubmodules.cmake)

set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/json/single_include)
include_directories(${JSON_INCLUDE_DIR})

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include)
include_directories(${SFML_INCLUDE_DIR})

set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/lib)
link_directories(${SFML_LIB_DIR})

add_subdirectory(external)
add_subdirectory(game)
add_subdirectory(graphic)
add_subdirectory(logic)
add_subdirectory(math)
add_subdirectory(ut)

file(COPY data DESTINATION "${CMAKE_BINARY_DIR}/bin")

set(CONFIGURATION "x86")
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
   set(CONFIGURATION "x64")
endif()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/extlibs/bin/${CONFIGURATION}/openal32.dll"
   DESTINATION "${CMAKE_BINARY_DIR}/bin"
   )