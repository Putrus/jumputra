#pragma once

#include "Kinematics.hpp"

namespace jp::game::physics
{
    class Wind final : public Kinematics
    {
    public:
        Wind(float acceleration, float velocity = 0.f);

        float getAcceleration() const;
        float getVelocity() const;

        void setAcceleration(float acceleration);
        void setVelocity(float velocity);
    };
}