#pragma once

#include "Graph.hpp"
#include "Properties.hpp"

namespace jp::algorithm
{
   class QGraph final : public Graph
   {
   public:
      QGraph(const Properties& properties);

      void insertEdge(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment,
         const std::shared_ptr<EdgeMove>& edgeMove) override;

   private:
      const Properties& mProperties;
   };
}