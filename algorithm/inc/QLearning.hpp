#pragma once

#include "Algorithm.hpp"

namespace jp::algorithm
{
   class QLearning final : public Algorithm
   {
   public:
      QLearning(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      void update(float dt) override;
   };
}