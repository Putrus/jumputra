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

   std::vector<Move> AntGraph::getShortestMovesPath(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment)
   {
      std::cout << "Getting shortest path" << std::endl;
      std::cout << *originSegment << " | " << *destinationSegment << std::endl;
      std::vector<Move> path;
      if (originSegment == destinationSegment)
      {
         return path;
      }
      std::map<std::shared_ptr<logic::Segment>, float> d;
      std::map<std::shared_ptr<logic::Segment>, std::shared_ptr<logic::Segment>> p;
      std::unordered_set<std::shared_ptr<logic::Segment>> Q;
      for (const auto& segment : mAdjacencyList)
      {
         Q.insert(segment.first);
         d.insert({ segment.first, std::numeric_limits<float>::max() });
         p.insert({ segment.first, nullptr });
         for (const auto& neighbour : segment.second)
         {
            d.insert({ neighbour.first, std::numeric_limits<float>::max() });
            p.insert({ neighbour.first, nullptr });
         }
      }

      d[originSegment] = 0;

      while (!Q.empty())
      {
         std::shared_ptr<logic::Segment> minSegment = nullptr;
         float minValue = std::numeric_limits<float>::max();
         for (const auto& segment : Q)
         {
            if (d.at(segment) < minValue)
            {
               minValue = d.at(segment);
               minSegment = segment;
            }
         }
         std::cout << "minValue = " << minValue << std::endl;

         for (const auto& [neighbour, move] : mAdjacencyList.at(minSegment))
         {
            float dValue = d.at(minSegment) + move->time;
            if (d.at(neighbour) > dValue)
            {
               d[neighbour] = dValue;
               p[neighbour] = minSegment;
            }
         }
         Q.erase(Q.find(minSegment));
      }

      std::shared_ptr<logic::Segment> currentSegment = destinationSegment;
      while (currentSegment != originSegment)
      {
         auto previousSegment = p.at(currentSegment);
         if (!previousSegment)
         {
            return {};
         }
         std::cout << "Pushing move: " << mAdjacencyList.at(previousSegment).at(currentSegment)->move << std::endl;
         path.push_back(mAdjacencyList.at(previousSegment).at(currentSegment)->move);
         currentSegment = previousSegment;
      }

      std::reverse(path.begin(), path.end());
      return path;
   }
}