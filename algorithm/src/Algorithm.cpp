#include "../inc/Algorithm.hpp"
#include "../inc/Dummy.hpp"
#include "../inc/Greedy.hpp"

#include <fstream>

namespace jp::algorithm
{
   Algorithm::Algorithm(const std::shared_ptr<logic::Engine>& engine)
      : mRandomGenerator(std::random_device{}()), mEngine(engine), Movable({}) {}

   void Algorithm::saveMoves(const std::string &filename) const
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

   Move Algorithm::randomMove() const
   {
      Move move;
      move.type = static_cast<MoveType>(randomInRange(0, 1));
      if (move.type == MoveType::Jump)
      {
         move.value = static_cast<float>(randomInRange(1, mEngine->getProperties().character.jump.max.y));
      }
      else
      {
         move.value = static_cast<float>(randomInRange(1, 100)) / 100.f;
      }
      move.direction = static_cast<logic::CharacterDirection>(randomInRange(1, 2));
      return move;
   }

   Move Algorithm::randomJump() const
   {
      Move move;
      move.type = MoveType::Jump;
      move.value = randomInRange(0, mEngine->getProperties().character.jump.max.y);
      move.direction = static_cast<logic::CharacterDirection>(randomInRange(1, 2));
      return move;
   }

   int Algorithm::randomInRange(int min, int max) const
   {
      std::uniform_int_distribution<std::mt19937::result_type> distrib(min, max);

      return distrib(mRandomGenerator);
   }
}