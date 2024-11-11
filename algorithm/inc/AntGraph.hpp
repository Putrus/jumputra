#pragma once

#include "Graph.hpp"
#include "Pheromone.hpp"

namespace jp::algorithm
{
   class AntGraph : public Graph
   {
   public:
      void insertPheromone(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment,
         const std::shared_ptr<Pheromone>& pheromone);

   };
}