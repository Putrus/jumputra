#include "../inc/Goal.hpp"

namespace jp::logic
{
   Goal::Goal(const math::Rect<float>& rect) : mRect(rect) {}

   bool Goal::checkWin(const math::Rect<float>& rect) const
   {
      return mRect.intersects(rect);
   }
}