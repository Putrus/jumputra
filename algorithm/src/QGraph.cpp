#include "../inc/QGraph.hpp"

namespace jp::algorithm
{
   QGraph::QGraph(const Properties& properties) : mProperties(properties) {}

   void QGraph::insertEdge(const std::shared_ptr<logic::Segment>& originSegment,
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
}