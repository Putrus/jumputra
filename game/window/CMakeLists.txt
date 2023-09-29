cmake_minimum_required(VERSION 3.0)

project(game-window)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ALL_FILES src/main.cpp
   inc/Game.hpp src/Game.cpp)

add_executable(game-window ${ALL_FILES})

set(CONFIGURATION x86)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(CONFIGURATION x64)
endif()

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/include)
set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/lib)
target_include_directories(game-window PRIVATE ${SFML_INCLUDE_DIR})
target_link_directories(game-window PRIVATE ${SFML_LIB_DIR})

target_link_libraries(game-window PRIVATE jp-game-engine sfml-graphics sfml-window sfml-audio sfml-system)