#pragma once

#include "Movable.hpp"
#include "Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <random>

namespace jp::algorithm
{
   enum class AlgorithmType : int
   {
      Genetic,
      Greedy
   };

   class Algorithm : public Movable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void saveMoves(const std::string &filename) const;

   protected:
      Move randomMove() const;
      Move randomJump() const;

      std::shared_ptr<logic::Engine> mEngine;
      const Properties& mProperties;
   };
}