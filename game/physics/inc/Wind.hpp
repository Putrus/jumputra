#pragma once

#include "Kinematics.hpp"

namespace jp::game::physics
{
    class Wind : public Kinematics
    {
    public:
        Wind(const math::Vector2<float>& maxVelocity, const math::Vector2<float>& acceleration,
            const math::Vector2<float>& velocity = math::Vector2<float>());

        math::Vector2<float> getMaxVelocity() const;

        void setMaxVelocity(const math::Vector2<float>& velocity);

    protected:
        math::Vector2<float> mMaxVelocity;
    };
}