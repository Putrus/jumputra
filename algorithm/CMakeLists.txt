cmake_minimum_required(VERSION 3.6..3.28)

project(jp_algorithm
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra algorithm"
)

set(HEADERS
   inc/Algorithm.hpp
   inc/Ant.hpp
   inc/AntColony.hpp
   inc/Bot.hpp
   inc/DecisionNode.hpp
   inc/DecisionTree.hpp
   inc/EdgeMove.hpp
   inc/Genetic.hpp
   inc/Greedy.hpp
   inc/Human.hpp
   inc/Movable.hpp
   inc/Move.hpp
   inc/Pheromone.hpp
   inc/Properties.hpp
   inc/QLearning.hpp
   inc/Wanderer.hpp
   )

set(SOURCES
   src/Algorithm.cpp
   src/Ant.cpp
   src/AntColony.cpp
   src/Bot.cpp
   src/DecisionNode.cpp
   src/DecisionTree.cpp
   src/EdgeMove.cpp
   src/Genetic.cpp
   src/Greedy.cpp
   src/Human.cpp
   src/Movable.cpp
   src/Move.cpp
   src/Pheromone.cpp
   src/Properties.cpp
   src/QLearning.cpp
   src/Wanderer.cpp
   )

add_library(jp_algorithm STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_algorithm PUBLIC jp_logic)
