#pragma once

#include "Bot.hpp"
#include "Properties.hpp"

#include "../../core/inc/Logger.hpp"

#include "../../logic/inc/Engine.hpp"

#include <vector>

namespace jp::algorithm
{
   enum class AlgorithmName
   {
      AntColony = 0,
      DecisionTree,
      Genetic,
      Greedy,
      Human,
      QLearning
   };

   std::ostream& operator<<(std::ostream& os, AlgorithmName name);

   class Algorithm : public Movable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      static std::unique_ptr<Algorithm> create(AlgorithmName name, const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      static AlgorithmName stringToName(const std::string& name);
      static std::string nameToString(AlgorithmName name);

      virtual std::string getName() const = 0;
      virtual void saveStatistics(const std::string& filename) const;

   protected:
      void addBot(const logic::Character& character, const std::vector<Move>& moves);
      void addBot(const logic::Character& character, const Move& move);
      void clearBots();
      
      bool haveBotsFinishedMoves() const;

      Move randomMove() const;
      Move randomJump() const;
      Move randomSideJump() const;

      std::vector<std::shared_ptr<Bot>> mBots;
      std::weak_ptr<logic::Engine> mEngine;
      std::shared_ptr<core::Logger> mLogger;
      const Properties& mProperties;
   };
}