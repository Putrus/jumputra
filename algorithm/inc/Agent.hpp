#pragma once

#include "Properties.hpp"
#include "QGraph.hpp"
#include "Wanderer.hpp"

#include "../../logic/inc/Engine.hpp"

#include <set>

namespace jp::algorithm
{
   class Agent final : public Wanderer
   {
   public:
      Agent(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, QGraph& graph);

   protected:
      virtual void afterMove(math::Vector2<float>& position) override;
      virtual void whileWander(math::Vector2<float>& position) override;

   private:
      QGraph& mGraph;
      std::shared_ptr<EdgeMove> mDestinationAction = nullptr;
      float mTMPTime = 0.f;
      math::Vector2<float> mTMPBestPosition = math::Vector2<float>(0.f, 90000.f);
   };
}