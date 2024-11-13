#include "../inc/Algorithm.hpp"
#include "../inc/AntColony.hpp"
#include "../inc/DecisionTree.hpp"
#include "../inc/Genetic.hpp"
#include "../inc/Greedy.hpp"
#include "../inc/Human.hpp"
#include "../inc/QLearning.hpp"

#include "../../core/inc/Random.hpp"
#include "../../core/inc/String.hpp"

#include <fstream>

namespace jp::algorithm
{
   std::ostream& operator<<(std::ostream& os, AlgorithmName name)
   {
      switch (name)
      {
         case AlgorithmName::AntColony:
         os << "AntColony";
         break;
         case AlgorithmName::DecisionTree:
         os << "DecisionTree";
         break;
         case AlgorithmName::Genetic:
         os << "Genetic";
         break;
         case AlgorithmName::Greedy:
         os << "Greedy";
         break;
         case AlgorithmName::Human:
         os << "Human";
         break;
         case AlgorithmName::QLearning:
         os << "QLearning";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Algorithm::Algorithm(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const  Properties& properties)
      : mEngine(engine), mProperties(properties), mLogger(logger), Movable({}) {}

   std::unique_ptr<Algorithm> Algorithm::create(AlgorithmName name, const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const Properties& properties)
   {
      switch (name)
      {
      case AlgorithmName::AntColony:
         return std::make_unique<algorithm::AntColony>(engine, logger, properties);
         break;
      case AlgorithmName::DecisionTree:
         return std::make_unique<algorithm::DecisionTree>(engine, logger, properties);
         break;
      case AlgorithmName::Genetic:
         return std::make_unique<algorithm::Genetic>(engine, logger, properties);
         break;
      case AlgorithmName::Greedy:
         return std::make_unique<algorithm::Greedy>(engine, logger, properties);
         break;
      case AlgorithmName::Human:
         return std::make_unique<algorithm::Human>(engine, logger, properties);
         break;
      case AlgorithmName::QLearning:
         return std::make_unique<algorithm::QLearning>(engine, logger, properties);
         break;
      default:
         throw std::invalid_argument("jp::Algorithm::create - Failed to create algorithm, wrong name");
      }
   }

   AlgorithmName Algorithm::stringToName(const std::string& name)
   {
      std::string algorithmName = core::String::toLower(name);
      if (algorithmName == "antcolony")
      {
         return AlgorithmName::AntColony;
      }
      else if (algorithmName == "decisiontree")
      {
         return AlgorithmName::DecisionTree;
      }
      else if (algorithmName == "genetic")
      {
         return AlgorithmName::Genetic;
      }
      else if (algorithmName == "greedy")
      {
         return AlgorithmName::Greedy;
      }
      else if (algorithmName == "human")
      {
         return AlgorithmName::Human;
      }
      else if (algorithmName == "qlearning")
      {
         return AlgorithmName::QLearning;
      }
      else
      {
         throw std::invalid_argument("jp::Algorithm::stringToName - Failed to convert to name, wrong string " + algorithmName);
      }
   }

   std::string Algorithm::nameToString(AlgorithmName name)
   {
      std::stringstream ss;
      ss << name;
      return core::String::toLower(ss.str());
   }

   void Algorithm::saveStatistics(const std::string& filename) const
   {
      if (auto lockedEngine = mEngine.lock())
      {
         *mLogger << "Moves: " << mMoves.size() << std::endl;
         for (size_t i = 0; i < mMoves.size();  ++i)
         {
            *mLogger << i << " " << mMoves.at(i) << std::endl;
         }
         *mLogger << "Statistics: " << lockedEngine->getStatistics() << std::endl;

         nlohmann::json json;
         json["completed"] = lockedEngine->getWinner() ? 1 : 0;
         json["properties"] = mProperties.toJson();
         json["totalStatistics"] = lockedEngine->getStatistics().toJson();
         json["movesSize"] = mMoves.size();
         for (const auto& move : mMoves)
         {
            json["moves"].push_back(move.toJson());
         }

         std::ofstream file(filename);
         file << json;
         file.close();
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::saveStatistics - Failed to save statistics, engine doesn't exist");
      }
   }

   void Algorithm::addBot(const logic::Character& character, const std::vector<Move>& moves)
   {
      if (auto lockedEngine = mEngine.lock())
      {
         lockedEngine->addCharacterCopy(character);
         mBots.push_back(std::make_shared<Bot>(lockedEngine->getCharacters().back(), moves));
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::addBot - Failed to add bot, engine doesn't exist");
      }
   }

   void Algorithm::addBot(const logic::Character& character, const Move& move)
   {
      if (auto lockedEngine = mEngine.lock())
      {
         lockedEngine->addCharacterCopy(character);
         std::vector<Move> moves = { move };
         mBots.push_back(std::make_shared<Bot>(lockedEngine->getCharacters().back(), moves));
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::addBot - Failed to add bot, engine doesn't exist");
      }
   }

   void Algorithm::clearBots()
   {
      if (auto lockedEngine = mEngine.lock())
      {
         mBots.clear();
         lockedEngine->removeAllCharacters();
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::clearBots - Failed to clear bots, engine doesn't exist");
      }
   }

   bool Algorithm::haveBotsFinishedMoves() const
   {
      return std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot->finishedMoves(); }) == mBots.end();
   }

   Move Algorithm::randomMove() const
   {
      if (auto lockedEngine = mEngine.lock())
      {
         return Move::random(1.f, lockedEngine->getProperties().character.jump.max.y, 0.1f, 1.f);
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::randomMove - Failed to create random move, engine doesn't exist");
      }
   }

   Move Algorithm::randomJump() const
   {
      if (auto lockedEngine = mEngine.lock())
      {
         return Move::randomJump(1.f, lockedEngine->getProperties().character.jump.max.y);
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::randomJump - Failed to create random jump, engine doesn't exist");
      }
   }

   Move Algorithm::randomSideJump() const
   {
      if (auto lockedEngine = mEngine.lock())
      {
         return Move::randomSideJump(1.f, lockedEngine->getProperties().character.jump.max.y);
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Algorithm::randomSideJump - Failed to create random side jump, engine doesn't exist");
      }
   }
}