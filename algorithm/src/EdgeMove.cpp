#include "../inc/EdgeMove.hpp"

namespace jp::algorithm
{
   EdgeMove::EdgeMove(const math::Vector2<float>& position, const Move& move, float value, float time)
      : position(position), move(move), value(value), time(time) {}

   std::ostream& operator<<(std::ostream& os, const EdgeMove& move)
   {
      os << "pos: (" << move.position << "), move: (" << move.move << "), value: " << move.value;
      return os;
   }
}