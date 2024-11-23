#include "../inc/Graph.hpp"

#include <unordered_set>

namespace jp::algorithm
{
   void Graph::insertEdge(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment,
      const std::shared_ptr<EdgeMove>& edgeMove)
   {
      auto originFind = mAdjacencyList.find(originSegment);
      if (originFind != mAdjacencyList.end())
      {
         auto destinationFind = originFind->second.find(destinationSegment);
         if (destinationFind != originFind->second.end() &&
            destinationFind->second->time < edgeMove->time)
         {
            return;
         }
      }

      mAdjacencyList[originSegment][destinationSegment] = edgeMove;
      mBackwardAdjacencyList[destinationSegment][originSegment] = edgeMove;
   }

   std::vector<Move> Graph::getShortestMovesPath(const std::shared_ptr<logic::Segment>& originSegment,
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
         path.push_back(mAdjacencyList.at(previousSegment).at(currentSegment)->move);
         currentSegment = previousSegment;
      }

      std::reverse(path.begin(), path.end());
      return path;
   }

   std::ostream& operator<<(std::ostream& os, const Graph& graph)
   {
      for (const auto& segment : graph.mAdjacencyList)
      {
         os << *segment.first << ": " << std::endl;
         for (const auto& neighbour : segment.second)
         {
            os << '(' << *neighbour.first << "), edge: (" << *neighbour.second << ')' << std::endl;
         }
         os << std::endl;
      }
      return os;
   }
}