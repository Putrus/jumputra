#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::physics
{
    class Kinematics
    {
    public:
        Kinematics(const math::Vector2<float>& acceleration, const math::Vector2<float>& velocity);

        const math::Vector2<float>& getAcceleration() const;
        const math::Vector2<float>& getVelocity() const;

        void setAcceleration(const math::Vector2<float>& acceleration);
        void setVelocity(const math::Vector2<float>& velocity);

    protected:
        math::Vector2<float> mAcceleration;
        math::Vector2<float> mVelocity;
    };
}