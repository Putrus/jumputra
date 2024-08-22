#pragma once

#include "Bot.hpp"
#include "Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <vector>

namespace jp::algorithm
{
   enum class AlgorithmType : int
   {
      Genetic,
      Greedy
   };

   class Algorithm : public Movable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void saveMoves(const std::string &filename) const;

   protected:
      void addBot(const logic::Character& character, const std::vector<Move>& moves);
      void addBot(const logic::Character& character, const Move& move);
      void clearBots();
      
      bool haveBotsFinishedMoves() const;

      Move randomMove() const;
      Move randomJump() const;
      Move randomSideJump() const;

      std::vector<std::shared_ptr<Bot>> mBots;
      std::shared_ptr<logic::Engine> mEngine;
      const Properties& mProperties;
   };
}