#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class Greedy final : public Algorithm
   {
   public:
      Greedy(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      void nextIteration(logic::Character bestJumper);

      float mLastY = 0.f;
   };
}