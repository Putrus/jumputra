#pragma once

#include "../../math/inc/Rect.hpp"

namespace jp::logic
{
   class Goal
   {
   public:
      Goal(const math::Rect<float>& rect);
      
      bool checkWin(const math::Rect<float>& rect) const;

   private:
      math::Rect<float> mRect;
   };
}