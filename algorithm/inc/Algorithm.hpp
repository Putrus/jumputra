#pragma once

#include "Move.hpp"

#include "../../logic/inc/Engine.hpp"

namespace jp::algorithm
{
   enum class AlgorithmName : int
   {
      Dummy = 0,
      Genetic,
      Greedy,
      Sequence
   };

   std::ostream& operator<<(std::ostream& os, AlgorithmName name);

   class Algorithm : public logic::Updatable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine);

      void saveMoves(const std::string &filename) const;

   protected:
      std::shared_ptr<logic::Engine> mEngine;
      std::vector<Move> mMoves;
   };
}