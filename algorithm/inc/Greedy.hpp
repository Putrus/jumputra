#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class Greedy final : public Algorithm
   {
   public:
      Greedy(const std::shared_ptr<logic::Engine> &engine, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      void addBot(const logic::Character& character, const Move& move);
      void clear();
      void nextIteration(logic::Character bestJumper);

      std::vector<Bot> mBots;
      float mLastY = 0.f;
   };
}