#include "../inc/Math.hpp"

namespace jp::math
{
   Vector2<float> abs(const Vector2<float>& vec)
   {
      return math::Vector2<float>(std::abs(vec.x), std::abs(vec.y));
   }
}
