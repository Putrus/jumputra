#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class Pheromone
   {
   public:
      Pheromone(Move move, float intensity);

      void evaporate(float dt);
      void increaseIntensity(float value);

      Move getMove() const;
      float getIntensity() const;

   private:
      Move mMove;
      float mIntensity = 0.f;
   };
}