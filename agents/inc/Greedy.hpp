#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Greedy final : public Agent
   {
   public:
      Greedy(size_t bots = 100);
      void control(const std::shared_ptr<logic::Engine>& engine) override;

   private:
      int randomInRange(int min, int max);

      std::vector<float> mTargetJumpPowers;
      size_t mBotsSize = 0;
      bool mSquatMustBeDone = false;
      float mLastY = 0.f;
   };
}