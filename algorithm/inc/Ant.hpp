#pragma once

#include "AntGraph.hpp"
#include "Properties.hpp"
#include "Wanderer.hpp"

#include "../../logic/inc/Engine.hpp"

#include <set>

namespace jp::algorithm
{
   class Ant final : public Wanderer
   {
   public:
      Ant(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, AntGraph& antGraph);

   protected:
      virtual void afterMove(math::Vector2<float>& position) override;
      virtual void whileWander(math::Vector2<float>& position) override;

   private:
      AntGraph& mGraph;
      std::shared_ptr<EdgeMove> mDestinationPheromone = nullptr;
   };
}