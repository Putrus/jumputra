#pragma once

namespace jp::game::physics
{
    struct Properties
    {
        float bounceFactor = 0.f;
        float checkCollisionDistance = 0.f;
        float fallVelocity = 0.f;
        float friction = 0.f;
        float gravity = 0.f;
        math::Vector2<float> entitySize = math::Vector2<float>();
    };
}