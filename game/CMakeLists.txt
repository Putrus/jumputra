cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "Jumputra game"
)

add_subdirectory(external)

set(HEADERS
   inc/Context.hpp
   inc/Eventable.hpp
   inc/Updatable.hpp
   menu/inc/SelectableItem.hpp
   menu/src/SelectableItem.cpp
   resources/inc/ResourceManager.hpp
   resources/inc/Resources.hpp
   states/inc/State.hpp
   states/inc/StateMenu.hpp
   states/inc/StateStack.hpp
   )

set(SOURCES
   src/Context.cpp
   src/main.cpp
   resources/src/Resources.cpp
   states/src/State.cpp
   states/src/StateMenu.cpp
   states/src/StateStack.cpp
   )

add_executable(jp_game ${HEADERS} ${SOURCES})

set_target_properties(jp_game PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "jumputra"
   )

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include)
target_include_directories(jp_game PUBLIC ${SFML_INCLUDE_DIR})

set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/lib)
target_link_directories(jp_game PUBLIC ${SFML_LIB_DIR})

target_link_libraries(jp_game PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)

file(COPY data DESTINATION "${CMAKE_BINARY_DIR}/bin")