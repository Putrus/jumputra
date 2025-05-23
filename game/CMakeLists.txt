cmake_minimum_required(VERSION 3.6)

project(jp_game
VERSION 0.0.3
LANGUAGES CXX
DESCRIPTION "jumputra game"
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
   inc/Segment.hpp
   inc/State.hpp
   inc/StateAlgorithmChoice.hpp
   inc/StateGame.hpp
   inc/StateLanguage.hpp
   inc/StateMainMenu.hpp
   inc/StateMenu.hpp
   inc/StatePause.hpp
   inc/StateStack.hpp
   inc/StateWin.hpp
   inc/StateWorldChoice.hpp
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
   src/Segment.cpp
   src/State.cpp
   src/StateAlgorithmChoice.cpp
   src/StateGame.cpp
   src/StateLanguage.cpp
   src/StateMainMenu.cpp
   src/StateMenu.cpp
   src/StatePause.cpp
   src/StateStack.cpp
   src/StateWin.cpp
   src/StateWorldChoice.cpp
   src/Wind.cpp
   )

add_executable(jp_game ${HEADERS} ${SOURCES})

set_target_properties(jp_game PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   OUTPUT_NAME "jumputra"
   )

target_link_libraries(jp_game PUBLIC jp_graphics jp_algorithm)
