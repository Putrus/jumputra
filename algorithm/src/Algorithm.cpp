#include "../inc/Algorithm.hpp"
#include "../inc/Dummy.hpp"
#include "../inc/Greedy.hpp"

#include "../../core/inc/Random.hpp"

#include <fstream>

namespace jp::algorithm
{
   Algorithm::Algorithm(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : mEngine(engine), mProperties(properties), Movable({}) {}

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

   void Algorithm::addBot(const logic::Character& character, const std::vector<Move>& moves)
   {
      mEngine->addCharacterCopy(character);
      mBots.push_back(Bot(mEngine->getCharacters().back(), moves));
   }

   void Algorithm::addBot(const logic::Character& character, const Move& move)
   {
      mEngine->addCharacterCopy(character);
      mBots.push_back(Bot(mEngine->getCharacters().back(), { move }));
   }

   void Algorithm::clearBots()
   {
      mBots.clear();
      mEngine->removeAllCharacters();
   }

   bool Algorithm::haveBotsFinishedMoves() const
   {
      return std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot.finishedMoves(); }) == mBots.end();
   }

   Move Algorithm::randomMove() const
   {
      return Move::random(1.f, mEngine->getProperties().character.jump.max.y, 0.1f, 1.f);
   }

   Move Algorithm::randomJump() const
   {
      return Move::randomJump(1.f, mEngine->getProperties().character.jump.max.y);
   }

   Move Algorithm::randomSideJump() const
   {
      return Move::randomSideJump(1.f, mEngine->getProperties().character.jump.max.y);
   }
}