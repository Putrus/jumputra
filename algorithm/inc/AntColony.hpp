#pragma once

#include "Algorithm.hpp"
#include "Ant.hpp"
#include "AntGraph.hpp"

#include <set>

namespace jp::algorithm
{
   class AntColony final : public Algorithm
   {
   public:
      AntColony(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      std::string getName() const override;
      void update(float dt) override;
      void fillMoves(const std::shared_ptr<logic::Character>& winner) override;

   private:
      void addAnt(const math::Rect<float>& rect);
      void clearAnts();

      std::vector<std::shared_ptr<Bot>>& mAnts = mBots;
      AntGraph mGraph;
   };
}