#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   struct EdgeMove
   {
      EdgeMove() = default;
      EdgeMove(const math::Vector2<float>& position, const Move& move, float value, float time);

      friend std::ostream& operator<<(std::ostream& os, const EdgeMove& move);

      math::Vector2<float> position;
      Move move;
      float value;
      float time;
   };

   std::ostream& operator<<(std::ostream& os, const EdgeMove& move);
}