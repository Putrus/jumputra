cmake_minimum_required(VERSION 3.6..3.28)

project(jp_game
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "Jumputra game"
)

set(HEADERS
   inc/Character.hpp
   inc/Context.hpp
   inc/Eventable.hpp
   inc/Game.hpp
   inc/Goal.hpp
   inc/Jumputra.hpp
   inc/Language.hpp
   inc/Menu.hpp
   inc/MenuItem.hpp
   inc/Properties.hpp
   inc/State.hpp
   inc/Segment.hpp
   inc/StateGame.hpp
   inc/StateMenu.hpp
   inc/StateStack.hpp
   inc/Wind.hpp
   )

set(SOURCES
   src/Character.cpp
   src/Context.cpp
   src/Game.cpp
   src/Goal.cpp
   src/Jumputra.cpp
   src/Language.cpp
   src/main.cpp
   src/Menu.cpp
   src/MenuItem.cpp
   src/Properties.cpp
   src/State.cpp
   src/Segment.cpp
   src/StateGame.cpp
   src/StateMenu.cpp
   src/StateStack.cpp
   src/Wind.cpp
   )

add_executable(jp_game ${HEADERS} ${SOURCES})

set_target_properties(jp_game PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "jumputra"
   )

target_link_libraries(jp_game PUBLIC jp_graphic jp_logic)
