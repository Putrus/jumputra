#pragma once

#include "EdgeMove.hpp"

namespace jp::algorithm
{
   class Pheromone : public EdgeMove
   {
   public:
      Pheromone() = default;
      Pheromone(const math::Vector2<float>& position, const Move& move, float intensity, float time);

      float& intensity = value;
   };
}