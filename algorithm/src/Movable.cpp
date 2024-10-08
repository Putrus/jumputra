#include "../inc/Movable.hpp"

#include <fstream>

namespace jp::algorithm
{
   Movable::Movable(const std::vector<Move>& moves) : mMoves(moves) {}

   void Movable::addMove(const Move& move)
   {
      mMoves.push_back(move);
   }

   void Movable::saveMoves(const std::string &filename) const
   {
      nlohmann::json json;
      for (const auto& move : mMoves)
      {
         json["moves"].push_back(move.toJson());
      }
      std::ofstream file(filename);
      file << json;
      file.close();
   }

   const std::vector<Move>& Movable::getMoves() const
   {
      return mMoves;
   }
}