#include "../inc/PhysicsProperties.hpp"

#include <fstream>

namespace jp::game::engine::physics
{
    PhysicsProperties::PhysicsProperties()
    {
        loadFromFile();
    }

    void PhysicsProperties::loadFromFile()
    {
        std::fstream file("data/properties/physics.jp");
        if (!file.is_open() || file.bad())
        {
            file.close();
            throw std::runtime_error("Failed to open file data/properties/physics.jp");
        }
        std::string key;
        file >> key >> mBounceFactor;
        file >> key >> mCheckCollisionDistance;
        file >> key >> mFallVelocity;
        file >> key >> mFriction;
        file >> key >> mGravity;
        file >> key >> mWindFactor;
        file >> key >> mWindMaxVelocity;
        file.close();
    }

    void PhysicsProperties::saveToFile() const
    {
        std::fstream file("data/properties/physics.jp");
        if (!file.is_open() || file.bad())
        {
            file.close();
            throw std::runtime_error("Failed to open file data/properties/physics.jp");
        }
        file << "bounceFactor" << mBounceFactor;
        file << "checkCollisionDistance" << mCheckCollisionDistance;
        file << "fallVelocity" << mFallVelocity;
        file << "friction" << mFriction;
        file << "gravity" << mGravity;
        file << "windFactor" << mWindFactor;
        file << "windMaxVelocity" << mWindMaxVelocity;
        file.close();
    }

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

    float PhysicsProperties::getWindMaxVelocity() const
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

    void PhysicsProperties::setWindMaxVelocity(float windMaxVelocity)
    {
        mWindMaxVelocity = windMaxVelocity;
    }
}