#include "../inc/Goal.hpp"

namespace jp::game
{
   Goal::Goal(const math::Rect<float>& rect)
      : graphic::Goal(rect), logic::Goal(rect) {}
}