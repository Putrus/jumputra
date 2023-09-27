cmake_minimum_required(VERSION 3.0)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(game src/main.cpp
    inc/Character.hpp src/Character.cpp
    inc/Game.hpp src/Game.cpp
    physics/inc/DiagonalPlatform.hpp physics/src/DiagonalPlatform.cpp
    physics/inc/Engine.hpp physics/src/Engine.cpp
    physics/inc/Entity.hpp physics/src/Entity.cpp
    physics/inc/EntityUpdater.hpp physics/src/EntityUpdater.cpp
    physics/inc/HorizontalPlatform.hpp physics/src/HorizontalPlatform.cpp
    physics/inc/Platform.hpp physics/src/Platform.cpp
    physics/inc/Properties.hpp physics/src/Properties.cpp
    physics/inc/Updater.hpp physics/src/Updater.cpp
    physics/inc/VerticalPlatform.hpp physics/src/VerticalPlatform.cpp
    physics/inc/Wind.hpp physics/src/Wind.cpp
    physics/inc/WindUpdater.hpp physics/src/WindUpdater.cpp
    math/inc/Rect.hpp math/inc/Segment.hpp math/inc/Vector2.hpp
    )

#    add_library(game SHARED src/main.cpp
#    physics/inc/DiagonalPlatform.hpp physics/src/DiagonalPlatform.cpp
#    physics/inc/Engine.hpp physics/src/Engine.cpp
#    physics/inc/Entity.hpp physics/src/Entity.cpp
#    physics/inc/EntityUpdater.hpp physics/src/EntityUpdater.cpp
#    physics/inc/HorizontalPlatform.hpp physics/src/HorizontalPlatform.cpp
#    physics/inc/Platform.hpp physics/src/Platform.cpp
#    physics/inc/Properties.hpp physics/src/Properties.cpp
#    physics/inc/Updater.hpp physics/src/Updater.cpp
#    physics/inc/VerticalPlatform.hpp physics/src/VerticalPlatform.cpp
#    physics/inc/Wind.hpp physics/src/Wind.cpp
#    physics/inc/WindUpdater.hpp physics/src/WindUpdater.cpp
#    math/inc/Rect.hpp math/inc/Segment.hpp math/inc/Vector2.hpp
#    )
