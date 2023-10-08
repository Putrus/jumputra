#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::engine::physics
{
    class Kinematics
    {
    public:
        Kinematics();
        Kinematics(const math::Vector2<float>& acceleration, const math::Vector2<float>& velocity);

        const math::Vector2<float>& getAcceleration() const;
        const math::Vector2<float>& getVelocity() const;

        void setAcceleration(const math::Vector2<float>& acceleration);
        void setAccelerationX(float x);
        void setAccelerationY(float y);
        void setVelocity(const math::Vector2<float>& velocity);
        void setVelocityX(float x);
        void setVelocityY(float y);

    protected:
        math::Vector2<float> mAcceleration;
        math::Vector2<float> mVelocity;
    };
}