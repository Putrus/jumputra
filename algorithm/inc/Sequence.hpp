#pragma once

#include "Algorithm.hpp"

namespace jp::algorithm
{
   class Sequence final : public Algorithm
   {
   public:
      Sequence(const std::shared_ptr<logic::Engine>& engine);

      void update(float dt) override;
   };
}