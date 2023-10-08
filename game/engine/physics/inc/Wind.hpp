#pragma once

#include "Kinematics.hpp"

namespace jp::game::engine::physics
{
    class Wind final : public Kinematics
    {
    public:
        Wind();
        Wind(const math::Vector2<float>& acceleration,
            const math::Vector2<float>& velocity = math::Vector2<float>(0.f));
    };
}