cmake_minimum_required(VERSION 3.6)

project(jp_algorithm
VERSION 0.0.1
LANGUAGES CXX
DESCRIPTION "jumputra algorithm"
)

set(HEADERS
   inc/Agent.hpp
   inc/Algorithm.hpp
   inc/Ant.hpp
   inc/AntColony.hpp
   inc/AntGraph.hpp
   inc/Bot.hpp
   inc/DecisionNode.hpp
   inc/DecisionTree.hpp
   inc/EdgeMove.hpp
   inc/Genetic.hpp
   inc/Graph.hpp
   inc/Greedy.hpp
   inc/Human.hpp
   inc/Movable.hpp
   inc/Move.hpp
   inc/Pheromone.hpp
   inc/Properties.hpp
   inc/QGraph.hpp
   inc/QLearning.hpp
   inc/Wanderer.hpp
   )

set(SOURCES
   src/Agent.cpp
   src/Algorithm.cpp
   src/Ant.cpp
   src/AntColony.cpp
   src/AntGraph.cpp
   src/Bot.cpp
   src/DecisionNode.cpp
   src/DecisionTree.cpp
   src/EdgeMove.cpp
   src/Genetic.cpp
   src/Graph.cpp
   src/Greedy.cpp
   src/Human.cpp
   src/Movable.cpp
   src/Move.cpp
   src/Pheromone.cpp
   src/Properties.cpp
   src/QGraph.cpp
   src/QLearning.cpp
   src/Wanderer.cpp
   )

add_library(jp_algorithm STATIC ${HEADERS} ${SOURCES})

target_link_libraries(jp_algorithm PUBLIC jp_logic)
