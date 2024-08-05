#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Greedy final : public Agent
   {
   public:
      Greedy(int botsNumber = 100);
      void control(const std::shared_ptr<logic::Engine>& engine) override;

   private:
      int randomInRange(int min, int max);

      struct Bot
      {
         float jumpPowerY = 0.f;
         logic::CharacterDirection direction = logic::CharacterDirection::Up;
      };

      std::vector<Bot> mBots;
      bool mSquatMustBeDone = false;
      float mLastY = 0.f;
      int mBotsNumber = 0;
   };
}