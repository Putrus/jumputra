#include "../inc/PhysicsProperties.hpp"

namespace jp::game::physics
{
    PhysicsProperties::PhysicsProperties(float bounce, float collision, float fall,
        float friction, float gravity, float windFactor, float windMaxVelocity)
        : mBounceFactor(bounce), mCheckCollisionDistance(collision), mFallVelocity(fall),
            mFriction(friction), mGravity(gravity), mWindFactor(windFactor), mWindMaxVelocity(windMaxVelocity)
    {}

    float PhysicsProperties::getBounceFactor() const
    {
        return mBounceFactor;
    }

    float PhysicsProperties::getCheckCollisionDistance() const
    {
        return mCheckCollisionDistance;
    }

    float PhysicsProperties::getFallVelocity() const
    {
        return mFallVelocity;
    }

    float PhysicsProperties::getFriction() const
    {
        return mFriction;
    }

    float PhysicsProperties::getGravity() const
    {
        return mGravity;
    }

    float PhysicsProperties::getWindFactor() const
    {
        return mWindFactor;
    }

    const math::Vector2<float>& PhysicsProperties::getEntitySize() const
    {
       return mEntitySize;
    }

    const math::Vector2<float>& PhysicsProperties::getWindAcceleration() const
    {
        return mWindAcceleration;
    }

    const math::Vector2<float>& PhysicsProperties::getWindMaxVelocity() const
    {
        return mWindMaxVelocity;
    }

    void PhysicsProperties::setBounceFactor(float bounceFactor)
    {
        mBounceFactor = bounceFactor;
    }

    void PhysicsProperties::setCheckCollisionDistance(float distance)
    {
        mCheckCollisionDistance = distance;
    }

    void PhysicsProperties::setFallVelocity(float velocity)
    {
        mFallVelocity = velocity;
    }

    void PhysicsProperties::setFriction(float friction)
    {
        mFriction = friction;
    }

    void PhysicsProperties::setGravity(float gravity)
    {
        mGravity = gravity;
    }

    void PhysicsProperties::setWindFactor(float windFactor)
    {
        mWindFactor = windFactor;
    }

    void PhysicsProperties::setEntitySize(const math::Vector2<float>& entitySize)
    {
       mEntitySize = entitySize;
    }

    void PhysicsProperties::setWindAcceleration(const math::Vector2<float>& windAcceleration)
    {
        mWindAcceleration = windAcceleration;
    }

    void PhysicsProperties::setWindMaxVelocity(const math::Vector2<float>& windMaxVelocity)
    {
        mWindMaxVelocity = windMaxVelocity;
    }
}