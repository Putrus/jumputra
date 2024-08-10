#pragma once

#include "Movable.hpp"

#include "../../logic/inc/Engine.hpp"

#include <random>

namespace jp::algorithm
{
   class Algorithm : public Movable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine);

      void saveMoves(const std::string &filename) const;

   protected:
      Move randomMove() const;
      Move randomJump() const;

      int randomInt(int min, int max) const;
      float randomFloat(float min, float max) const;

      mutable std::mt19937 mRandomGenerator;

      std::shared_ptr<logic::Engine> mEngine;
   };
}