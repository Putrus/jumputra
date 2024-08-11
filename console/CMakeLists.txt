cmake_minimum_required(VERSION 3.6..3.28)

project(jp_console
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra console"
)

set(HEADERS
   inc/Consolutra.hpp
   inc/Properties.hpp
   )

set(SOURCES
   src/Consolutra.cpp
   src/main.cpp
   src/Properties.cpp
   )

add_executable(jp_console ${HEADERS} ${SOURCES})

set_target_properties(jp_console PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "consolutra"
   )

target_link_libraries(jp_console PUBLIC jp_algorithm)
