#include "../inc/Graph.hpp"

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