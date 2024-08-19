#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class DecisionTree final : public Algorithm
   {
   public:
      DecisionTree(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      std::vector<Bot> mBots;
      math::Vector2<float> mLastRunPosition = math::Vector2<float>();
      logic::CharacterDirection mRunDirection = logic::CharacterDirection::Right;
   };
}