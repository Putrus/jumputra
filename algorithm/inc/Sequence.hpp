#pragma once

#include "Algorithm.hpp"

namespace jp::algorithm
{
   class Sequence final : public Algorithm
   {
   public:
      Sequence(const std::vector<Move>& moves, const std::shared_ptr<logic::Engine>& engine);

      void update(float dt) override;

      bool isFinished() const;

   private:
      void nextMove();
      
      size_t mCurrentMoveId = 0;
      float mCurrentMoveValue = 0.f;
      bool mFinished = false;
   };
}