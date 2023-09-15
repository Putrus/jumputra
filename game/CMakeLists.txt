cmake_minimum_required(VERSION 3.0)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game main.cpp math/Rect.hpp math/Vector2.hpp)
