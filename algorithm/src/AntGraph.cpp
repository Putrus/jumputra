#include "../inc/AntGraph.hpp"

#include "../../core/inc/Random.hpp"

#include <unordered_set>

namespace jp::algorithm
{
   AntGraph::AntGraph(const Properties& properties) : mProperties(properties) {}

   void AntGraph::update(float dt)
   {
      for (auto& segment : mAdjacencyList)
      {
         for (auto& pheromone : segment.second)
         {
            pheromone.second->value = std::max(0.f, pheromone.second->value - dt * mProperties.antColony.evaporationRate);
         }
      }
   }

   void AntGraph::insertPheromone(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment,
      const std::shared_ptr<Pheromone>& pheromone,
      core::Logger& logger)
   {
      auto originFind = mAdjacencyList.find(originSegment);
      if (originFind != mAdjacencyList.end())
      {
         auto destinationFind = originFind->second.find(destinationSegment);
         if (destinationFind != originFind->second.end())
         {
            if (destinationFind->second->time < pheromone->time)
            {
               destinationFind->second->value = std::min(mProperties.antColony.maxIntensity,
                  destinationFind->second->value + pheromone->intensity);
               return;
            }
            else
            {
               pheromone->intensity = std::min(mProperties.antColony.maxIntensity,
                  pheromone->intensity + destinationFind->second->value);
            }
         }
         else
         {
            logger << "New pheromone between segments (" << *originSegment << ") and (" << *destinationSegment << ")" << std::endl;
         }
      }

      mAdjacencyList[originSegment][destinationSegment] = pheromone;
      mBackwardAdjacencyList[destinationSegment][originSegment] = pheromone;
   }

   std::shared_ptr<EdgeMove> AntGraph::getDestinationPheromone(const std::shared_ptr<logic::Segment>& segment) const
   {
      auto segmentFind = mAdjacencyList.find(segment);
      if (segmentFind != mAdjacencyList.end())
      {
         for (const auto& pheromone : segmentFind->second)
         {
            if (core::Random::getFloat(0.f, mProperties.antColony.maxIntensity) <= pheromone.second->value)
            {
               return pheromone.second;
            }
         }
      }
      return nullptr;
   }
}