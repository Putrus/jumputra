cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Jumputra game"
   )

set(HEADERS)
set(SOURCES
   src/main.cpp
   )

add_executable(jp_game ${HEADERS} ${SOURCES})

set_target_properties(jp_game PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "jumputra"
   )

add_subdirectory(external)