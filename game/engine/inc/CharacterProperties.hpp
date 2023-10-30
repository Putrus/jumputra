#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::engine
{
    struct CharacterProperties
    {
        CharacterProperties();
        CharacterProperties(const math::Vector2<float>& jumpGain,
            const math::Vector2<float>& jumpMax, float runVelocity);

        math::Vector2<float> jumpGain = math::Vector2<float>();
        math::Vector2<float> jumpMax = math::Vector2<float>();
        float runVelocity = 0.f;
    };
}