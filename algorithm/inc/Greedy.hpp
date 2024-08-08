#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class Greedy final : public Algorithm
   {
   public:
      Greedy(const std::shared_ptr<logic::Engine> &engine, size_t bots = 100);

      void update(float dt) override;

   private:
      int randomInRange(int min, int max);

      void nextIteration(const logic::Character &character);

      std::map<size_t, logic::Character> mCharactersThatLanded;
      std::vector<Bot> mBots;
      size_t mBotsSize = 0;
      float mLastY = 0.f;
   };
}