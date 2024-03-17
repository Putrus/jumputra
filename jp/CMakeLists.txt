cmake_minimum_required(VERSION 3.6..3.28)

project(jp
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "Jumputra"
)

add_subdirectory(external)

set(HEADERS
   inc/Jumputra.hpp
   states/inc/State.hpp
   states/inc/StateMenu.hpp
   states/inc/StateStack.hpp
   )

set(SOURCES
   src/Jumputra.cpp
   src/main.cpp
   states/src/State.cpp
   states/src/StateMenu.cpp
   states/src/StateStack.cpp
   )

add_executable(jp ${HEADERS} ${SOURCES})

set_target_properties(jp PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "jumputra"
   )

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include)
target_include_directories(jp PUBLIC ${SFML_INCLUDE_DIR})

set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/lib)
target_link_directories(jp PUBLIC ${SFML_LIB_DIR})

target_link_libraries(jp PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)

file(COPY data DESTINATION "${CMAKE_BINARY_DIR}/bin")