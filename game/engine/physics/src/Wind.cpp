#include "../inc/Wind.hpp"

namespace jp::game::engine::physics
{
    Wind::Wind(float acceleration, float velocity/* = 0.f*/)
    : mAcceleration(acceleration), mVelocity(velocity)
    {}

    float Wind::getAcceleration() const
    {
        return mAcceleration;
    }

    float Wind::getVelocity() const
    {
        return mVelocity;
    }

    void Wind::setAcceleration(float acceleration)
    {
        mAcceleration = acceleration;
    }

    void Wind::setVelocity(float velocity)
    {
        mVelocity = velocity;
    }
}