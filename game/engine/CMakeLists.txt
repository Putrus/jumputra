cmake_minimum_required(VERSION 3.0)

project(game-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(${CMAKE_CURRENT_SOURCE_DIR})
set(ALL_FILES
    src/main.cpp
    inc/Character.hpp src/Character.cpp
    math/inc/Rect.hpp math/inc/Segment.hpp math/inc/Vector2.hpp
    physics/inc/DiagonalPlatform.hpp physics/src/DiagonalPlatform.cpp
    physics/inc/Entity.hpp physics/src/Entity.cpp
    physics/inc/EntityUpdater.hpp physics/src/EntityUpdater.cpp
    physics/inc/HorizontalPlatform.hpp physics/src/HorizontalPlatform.cpp
    physics/inc/PhysicsEngine.hpp physics/src/PhysicsEngine.cpp
    physics/inc/PhysicsProperties.hpp physics/src/PhysicsProperties.cpp
    physics/inc/Platform.hpp physics/src/Platform.cpp
    physics/inc/Updater.hpp physics/src/Updater.cpp
    physics/inc/Wind.hpp physics/src/Wind.cpp
    physics/inc/WindUpdater.hpp physics/src/WindUpdater.cpp
    physics/inc/VerticalPlatform.hpp physics/src/VerticalPlatform.cpp
    )

add_executable(game-engine ${ALL_FILES})
add_library(jp-game-engine SHARED ${ALL_FILES})
set_target_properties(jp-game-engine PROPERTIES PREFIX "")
