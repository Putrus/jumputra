#pragma once

#include "Bot.hpp"

namespace jp::algorithm
{
   class Ant final : public Bot
   {
   public:
      Ant(const std::shared_ptr<logic::Character>& character);

      virtual void update(float dt) override;

   private:
      logic::CharacterDirection mLastDirection = logic::CharacterDirection::Left;
      math::Vector2<float> mLastPosition = math::Vector2<float>();
   };
}