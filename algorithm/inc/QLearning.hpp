#pragma once

#include "Algorithm.hpp"
#include "QGraph.hpp"
#include "Wanderer.hpp"

namespace jp::algorithm
{
   class QLearning final : public Algorithm
   {
   public:
      QLearning(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      std::string getName() const override;
      void update(float dt) override;
      void fillMoves(const std::shared_ptr<logic::Character>& winner) override;

   private:    
      std::vector<std::shared_ptr<Bot>>& mAgents = mBots;
      QGraph mGraph;
   };
}