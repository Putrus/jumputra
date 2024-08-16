#pragma once

#include "Bot.hpp"
#include "Pheromone.hpp"

namespace jp::algorithm
{
   class Ant final : public Bot
   {
   public:
      Ant(std::map<math::Vector2<float>, std::vector<Pheromone>>& pheromones, const std::shared_ptr<logic::Character>& character);

      virtual void update(float dt) override;

   private:
      void setMove(const Move& move);

      logic::CharacterDirection mLastDirection = logic::CharacterDirection::Left;
      math::Vector2<float> mLastPosition = math::Vector2<float>();
      math::Vector2<float> mLastChangeDirectionPosition = math::Vector2<float>();
      std::map<math::Vector2<float>, std::vector<Pheromone>>& mPheromones;
   };
}