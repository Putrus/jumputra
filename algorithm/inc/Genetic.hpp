#pragma once

#include "Algorithm.hpp"

namespace jp::algorithm
{
   class Genetic final : public Algorithm
   {
   public:
      Genetic(const std::shared_ptr<logic::Engine>& engine);

      void update(float dt) override;
   };
}