#include "../inc/AntGraph.hpp"

namespace jp::algorithm
{
   void AntGraph::insertPheromone(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment,
      const std::shared_ptr<Pheromone>& pheromone)
   {
      auto originFind = mAdjacencyList.find(originSegment);
      if (originFind != mAdjacencyList.end())
      {
         auto destinationFind = originFind->second.find(destinationSegment);
         if (destinationFind != originFind->second.end())
         {
            if (destinationFind->second->time < pheromone->time)
            {
               destinationFind->second->value += pheromone->intensity;
               return;
            }
            else
            {
               pheromone->intensity += destinationFind->second->value;
            }
         }
      }

      mAdjacencyList[originSegment][destinationSegment] = pheromone;
      mBackwardAdjacencyList[destinationSegment][originSegment] = pheromone;
   }
}