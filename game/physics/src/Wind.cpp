#include "../inc/Wind.hpp"

#include <cmath>

namespace jp::game::physics
{
    Wind::Wind(float acceleration, float maxVelocity, float velocity /*= 0.f*/)
    : mAcceleration(acceleration), mMaxVelocity(maxVelocity), mVelocity(velocity)
    {}

    float Wind::getVelocity() const
    {
        return mVelocity;
    }

    void UpdatableWind::update(float dt)
    {
        mVelocity += mAcceleration * dt;
        float absVelocity = std::abs(mVelocity);
        if (absVelocity >= mMaxVelocity)
        {
            mVelocity = mMaxVelocity * (mVelocity / absVelocity);
            mAcceleration *= -1.f;
        }
    }
}