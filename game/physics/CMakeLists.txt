cmake_minimum_required(VERSION 3.0)

project(jp-game-physics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    inc/DiagonalPlatform.hpp src/DiagonalPlatform.cpp
    inc/Entity.hpp src/Entity.cpp
    inc/EntityUpdater.hpp src/EntityUpdater.cpp
    inc/HorizontalPlatform.hpp src/HorizontalPlatform.cpp
    inc/Kinematics.hpp src/Kinematics.cpp
    inc/PhysicsEngine.hpp src/PhysicsEngine.cpp
    inc/PhysicsProperties.hpp src/PhysicsProperties.cpp
    inc/Platform.hpp src/Platform.cpp
    inc/Updater.hpp src/Updater.cpp
    inc/Wind.hpp src/Wind.cpp
    inc/WindUpdater.hpp src/WindUpdater.cpp
    inc/VerticalPlatform.hpp src/VerticalPlatform.cpp
    )

add_library(jp-game-physics STATIC ${SOURCE_FILES})