cmake_minimum_required(VERSION 3.0)

project(jp-game-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SOURCE_FILES
    src/main.cpp
    inc/Character.hpp src/Character.cpp
    inc/Engine.hpp src/Engine.cpp
    inc/PlatformsManager.hpp src/PlatformsManager.cpp
    inc/PropertiesManager.hpp src/PropertiesManager.cpp
    )

add_library(jp-game-engine SHARED ${SOURCE_FILES})

target_include_directories(jp-game-engine PRIVATE ${EXT_INCLUDE_DIR})
target_link_libraries(jp-game-engine PRIVATE jp-game-math jp-game-physics)