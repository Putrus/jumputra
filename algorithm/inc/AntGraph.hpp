#pragma once

#include "Graph.hpp"
#include "Pheromone.hpp"
#include "Properties.hpp"

namespace jp::algorithm
{
   class AntGraph final : public Graph, public logic::Updatable
   {
   public:
      AntGraph(const Properties& properties);
      void update(float dt) override;

      void insertPheromone(const std::shared_ptr<logic::Segment>& originSegment,
         const std::shared_ptr<logic::Segment>& destinationSegment,
         const std::shared_ptr<Pheromone>& pheromone);

      std::shared_ptr<EdgeMove> getDestinationPheromone(const std::shared_ptr<logic::Segment>& segment) const;

   private:
      const Properties& mProperties;
      float mTMPTime = 0.f;
   };
}