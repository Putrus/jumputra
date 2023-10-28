cmake_minimum_required(VERSION 3.0)

project(jp-game-view)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp
   inc/Game.hpp src/Game.cpp
   inc/Wind.hpp src/Wind.cpp
   )

add_executable(jp-game-view ${SOURCE_FILES})

set(CONFIGURATION x86)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(CONFIGURATION x64)
endif()

#set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/lib/cmake/SFML)
set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/include)
set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/lib)

target_include_directories(jp-game-view PRIVATE ${SFML_INCLUDE_DIR})

target_link_directories(jp-game-view PRIVATE ${SFML_LIB_DIR})

#set(SFML_STATIC_LIBRARIES TRUE)
#find_package(SFML 2.6.0 COMPONENTS graphics audio window system REQUIRED)
target_link_libraries(jp-game-view PRIVATE jp-game-engine jp-game-math jp-game-physics sfml-graphics sfml-window sfml-audio sfml-system)