#pragma once

#include "WindProperties.hpp"

#include "../../math/inc/Vector2.hpp"

namespace jp::game::physics
{
    struct PhysicsProperties
    {
        PhysicsProperties();
        PhysicsProperties(float bounce, float collision, float fall,
            float friction, float gravity, const WindProperties& windProperties);

        float bounceFactor = 0.f;
        float checkCollisionDistance = 0.f;
        float fallVelocity = 0.f;
        float friction = 0.f;
        float gravity = 0.f;
        math::Vector2<float> entitySize = math::Vector2<float>();

        WindProperties wind;
    };
}