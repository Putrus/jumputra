cmake_minimum_required(VERSION 3.6..3.28)

project(jumputra
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Comparative Analysis of Metaheuristics, Machine Learning, and Human in a Platform Game"
   )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/UpdateSubmodules.cmake)

add_subdirectory(math)
add_subdirectory(ut)