#include "../inc/Algorithm.hpp"
#include "../inc/Dummy.hpp"
#include "../inc/Greedy.hpp"

#include <fstream>

constexpr float FLOAT_PRECISION = 10000.f;

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
      move.type = static_cast<MoveType>(randomInt(0, 1));
      if (move.type == MoveType::Jump)
      {
         move.value = randomFloat(1.f, mEngine->getProperties().character.jump.max.y);
      }
      else
      {
         move.value = randomFloat(0.1f, 1.f);
      }
      move.direction = static_cast<logic::CharacterDirection>(randomInt(1, 2));
      return move;
   }

   Move Algorithm::randomJump() const
   {
      Move move;
      move.type = MoveType::Jump;
      move.value = randomFloat(0.f, mEngine->getProperties().character.jump.max.y);
      move.direction = static_cast<logic::CharacterDirection>(randomInt(1, 2));
      return move;
   }

   int Algorithm::randomInt(int min, int max) const
   {
      std::uniform_int_distribution<std::mt19937::result_type> distrib(min, max);

      return distrib(mRandomGenerator);
   }

   float Algorithm::randomFloat(float min, float max) const
   {
      int intMin = static_cast<int>(min * FLOAT_PRECISION);
      int intMax = static_cast<int>(max * FLOAT_PRECISION);
      std::uniform_int_distribution<std::mt19937::result_type> distrib(intMin, intMax);

      return static_cast<float>(distrib(mRandomGenerator)) / FLOAT_PRECISION;
   }
}