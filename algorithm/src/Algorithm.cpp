#include "../inc/Algorithm.hpp"

#include "../../core/inc/Random.hpp"

#include <fstream>

namespace jp::algorithm
{
   Algorithm::Algorithm(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mEngine(engine), mProperties(properties), mLogger(logger), Movable({}) {}

   void Algorithm::saveStatistics(const std::string& filename) const
   {
      *mLogger << "Moves: " << mMoves.size() << std::endl;
      for (size_t i = 0; i < mMoves.size();  ++i)
      {
         *mLogger << i << " " << mMoves.at(i) << std::endl;
      }
      *mLogger << "Statistics: " << mEngine->getStatistics() << std::endl;

      nlohmann::json json;
      json["totalStatistics"] = mEngine->getStatistics().toJson();
      json["movesSize"] = mMoves.size();
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
      mBots.push_back(std::make_shared<Bot>(mEngine->getCharacters().back(), moves));
   }

   void Algorithm::addBot(const logic::Character& character, const Move& move)
   {
      mEngine->addCharacterCopy(character);
      std::vector<Move> moves = { move };
      mBots.push_back(std::make_shared<Bot>(mEngine->getCharacters().back(), moves));
   }

   void Algorithm::clearBots()
   {
      mBots.clear();
      mEngine->removeAllCharacters();
   }

   bool Algorithm::haveBotsFinishedMoves() const
   {
      return std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot->finishedMoves(); }) == mBots.end();
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