cmake_minimum_required(VERSION 3.6..3.28)

project(jp_graphic
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra graphic"
)

add_subdirectory(external)

set(HEADERS)

set(SOURCES)

add_library(jp_graphic STATIC ${HEADERS} ${SOURCES})

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include)
target_include_directories(jp_graphic PUBLIC ${SFML_INCLUDE_DIR})

set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/lib)
target_link_directories(jp_graphic PUBLIC ${SFML_LIB_DIR})

target_link_libraries(jp_graphic PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)
