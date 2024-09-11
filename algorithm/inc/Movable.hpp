#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class Movable : public logic::Updatable
   {
   public:
      Movable(const std::vector<Move>& moves);

      void addMove(const Move& move);

      void saveMoves(const std::string& filename) const;

      const std::vector<Move>& getMoves() const;

   protected:
      std::vector<Move> mMoves;
   };
}