#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::physics
{
   struct PhysicsProperties
   {
      float bounceFactor = 0.f;
      float checkCollisionDistance = 0.f;
      float fallVelocity = 0.f;
      float slipperyFriction = 0.f;
      math::Vector2<float> gravity = 0.f;
      math::Vector2<float> bodySize = 0.f;
   };
}