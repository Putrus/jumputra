cmake_minimum_required(VERSION 3.0)

project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
   ${CMAKE_SOURCE_DIR}/common
   ${CMAKE_SOURCE_DIR}/engine
   ${CMAKE_SOURCE_DIR}/math
   ${CMAKE_SOURCE_DIR}/physics
   ${CMAKE_SOURCE_DIR}/window)

set(EXT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)

add_subdirectory(engine)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(view)
