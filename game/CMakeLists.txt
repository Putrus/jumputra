cmake_minimum_required(VERSION 3.0)

project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/engine ${CMAKE_SOURCE_DIR}/window)

add_subdirectory(engine)
add_subdirectory(window)
