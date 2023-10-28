#pragma once

namespace jp::game::physics
{
    struct WindProperties
    {
        WindProperties();
        WindProperties(float acceleration, float factor, float maxVelocity, float startPosition, float endPosition);

        float acceleration = 0.f;
        float factor = 0.f;
        float maxVelocity = 0.f;
        float startPosition = 0.f;
        float endPosition = 0.f;
    };
}