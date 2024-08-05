#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Greedy final : public Agent
   {
   public:
      Greedy(const std::shared_ptr<logic::Engine> &engine, size_t bots = 100);

      void update(float dt) override;

   private:
      int randomInRange(int min, int max);

      void nextIteration(const logic::Character &character);

      std::map<size_t, logic::Character> mCharactersThatLanded;
      std::vector<Move> mTargetMoves;
      size_t mBotsSize = 0;
      bool mSquatMustBeDone = false;
      float mLastY = 0.f;
   };
}