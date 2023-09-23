#include "../inc/Properties.hpp"

namespace jp::game::physics
{
    Properties::Properties(float gravity, float checkCollisionDistance,
        float bounceFactor, float windFactor, float windMaxVelocity)
        : mGravity(gravity), mCheckCollisionDistance(checkCollisionDistance),
        mBounceFactor(bounceFactor), mWindFactor(windFactor), mWindMaxVelocity(windMaxVelocity)
    {}
        
    float Properties::getGravity() const
    {
        return mGravity;
    }

    float Properties::getCheckCollisionDistance() const
    {
        return mCheckCollisionDistance;
    }

    float Properties::getBounceFactor() const
    {
        return mBounceFactor;
    }

    float Properties::getFriction() const
    {
        return mFriction;
    }

    float Properties::getWindFactor() const
    {
        return mWindFactor;
    }

    float Properties::getWindMaxVelocity() const
    {
        return mWindMaxVelocity;
    }

    void Properties::setGravity(float gravity)
    {
        mGravity = gravity;
    }

    void Properties::setCheckCollisionDistance(float checkCollisionDistance)
    {
        mCheckCollisionDistance = checkCollisionDistance;
    }

    void Properties::setBounceFactor(float bounceFactor)
    {
        mBounceFactor = bounceFactor;
    }

    void Properties::setFriction(float friction)
    {
        mFriction = friction;
    }

    void Properties::setWindFactor(float windFactor)
    {
        mWindFactor = windFactor;
    }

    void Properties::setWindMaxVelocity(float windMaxVelocity)
    {
        mWindMaxVelocity = windMaxVelocity;
    }
}