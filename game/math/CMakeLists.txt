cmake_minimum_required(VERSION 3.0)

project(jp-game-math)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    inc/Rect.hpp
    inc/Segment.hpp
    inc/Vector2.hpp
    inc/Function.hpp src/Function.cpp
    )

add_library(jp-game-math STATIC ${SOURCE_FILES})