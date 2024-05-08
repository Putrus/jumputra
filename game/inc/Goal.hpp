#pragma once

#include "../../graphic/inc/Goal.hpp"
#include "../../logic/inc/Goal.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Goal : public graphic::Goal, public logic::Goal
   {
   public:
      Goal(const math::Rect<float>& rect);
   };
}