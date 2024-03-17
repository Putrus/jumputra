project(jp_ut
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Unit tests for the jumputra project"
   )

include(CTest)

add_subdirectory(external)
add_subdirectory(math)