#pragma once

#include "../../physics/inc/Body.hpp"

namespace jp::game::logic
{
   typedef physics::BodyState CharacterState;

   class Character : physics::Body
   {
   public:
      Character(const math::Vector2<float>& position,
         const math::Vector2<float>& size);
      Character(const math::Rect<float>& rect);
   };
}