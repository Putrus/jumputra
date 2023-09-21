#include "../inc/Wind.hpp"

namespace jp::game::physics
{
    Wind::Wind(float acceleration, float velocity/* = 0.f*/)
    : Kinematics(math::Vector2<float>(acceleration, 0.f), math::Vector2<float>(velocity, 0.f))
    {}

    float Wind::getAcceleration() const
    {
        return mAcceleration.x;
    }

    float Wind::getVelocity() const
    {
        return mVelocity.x;
    }

    void Wind::setAcceleration(float acceleration)
    {
        mAcceleration.x = acceleration;
    }

    void Wind::setVelocity(float velocity)
    {
        mVelocity.x = velocity;
    }
}