#pragma once

#include "Bot.hpp"
#include "Pheromone.hpp"
#include "Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <set>

namespace jp::algorithm
{
   class Ant final : public Bot
   {
   public:
      Ant(std::vector<std::shared_ptr<Pheromone>>& pheromones,
         const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character);

      virtual void update(float dt) override;

   private:
      void setMove(const Move& move);

      math::Vector2<float> mLastChangeDirectionPosition = math::Vector2<float>();
      math::Vector2<float> mLastPosition = math::Vector2<float>();
      std::shared_ptr<logic::Segment> mSegmentBeforeJump;
      const Properties& mProperties;
      std::vector<std::shared_ptr<Pheromone>>& mPheromones;
   };
}