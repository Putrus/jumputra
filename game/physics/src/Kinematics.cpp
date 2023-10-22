#include "../inc/Kinematics.hpp"

namespace jp::game::physics
{
    Kinematics::Kinematics() : mAcceleration(0.f), mVelocity(0.f)
    {}
    
    Kinematics::Kinematics(const math::Vector2<float>& acceleration, const math::Vector2<float>& velocity)
        : mAcceleration(acceleration), mVelocity(velocity)
    {}

    const math::Vector2<float>& Kinematics::getAcceleration() const
    {
        return mAcceleration;
    }

    const math::Vector2<float>& Kinematics::getVelocity() const
    {
        return mVelocity;
    }

    void Kinematics::setAcceleration(const math::Vector2<float>& acceleration)
    {
        mAcceleration = acceleration;
    }

    void Kinematics::setAccelerationX(float x)
    {
        mAcceleration.x = x;
    }

    void Kinematics::setAccelerationY(float y)
    {
        mAcceleration.y = y;
    }

    void Kinematics::setVelocity(const math::Vector2<float>& velocity)
    {
        mVelocity = velocity;
    }

    void Kinematics::setVelocityX(float x)
    {
        mVelocity.x = x;
    }

    void Kinematics::setVelocityY(float y)
    {
        mVelocity.y = y;
    }
}