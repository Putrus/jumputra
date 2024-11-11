#pragma once

#include "EdgeMove.hpp"

#include "../../logic/inc/Segment.hpp"

#include <map>

namespace jp::algorithm
{
   class Graph
   {
   public:
      void insertEdge(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment,
         const std::shared_ptr<EdgeMove>& edgeMove);

      bool doesEdgeExists(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment) const;

      friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

   protected:
      std::unordered_map<std::shared_ptr<logic::Segment>,
          std::unordered_map<std::shared_ptr<logic::Segment>, std::shared_ptr<EdgeMove>>> mAdjacencyList;
      std::unordered_map<std::shared_ptr<logic::Segment>,
          std::unordered_map<std::shared_ptr<logic::Segment>, std::shared_ptr<EdgeMove>>> mBackwardAdjacencyList;
   };

   std::ostream& operator<<(std::ostream& os, const Graph& graph);
}