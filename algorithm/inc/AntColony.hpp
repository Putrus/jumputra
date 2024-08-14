#pragma once

#include "Algorithm.hpp"
#include "Ant.hpp"

namespace jp::algorithm
{
   class AntColony final : public Algorithm
   {
   public:
      AntColony(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      std::vector<Ant> mAnts;
   };
}