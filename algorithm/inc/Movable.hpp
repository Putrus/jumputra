#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class Movable : public logic::Updatable
   {
   public:
      Movable(const std::vector<Move>& moves);

      void saveMoves(const std::string& filename) const;

   protected:
      std::vector<Move> mMoves;
   };
}