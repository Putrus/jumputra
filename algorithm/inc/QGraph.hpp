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

      std::shared_ptr<EdgeMove> getBestAction(const std::shared_ptr<logic::Segment>& segment) const;
      std::shared_ptr<EdgeMove> getRandomAction(const std::shared_ptr<logic::Segment>& segment) const;

   private:
      float getQ(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment) const;
      float getMaxQ(const std::shared_ptr<logic::Segment>& segment) const;

      const Properties& mProperties;
   };
}