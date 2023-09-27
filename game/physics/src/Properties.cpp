#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::game::physics
{
    Properties::Properties()
    {
        loadFromFile();
    }

    void Properties::loadFromFile()
    {
        std::fstream file("data/properties/physics.jp");
        if (!file.is_open() || file.bad())
        {
            file.close();
            throw std::runtime_error("Failed to open file data/properties/physics.jp");
        }
        std::string key;
        float value;
        file >> key >> mBounceFactor;
        file >> key >> mCheckCollisionDistance;
        file >> key >> mFallVelocity;
        file >> key >> mFriction;
        file >> key >> mGravity;
        file >> key >> mWindFactor;
        file >> key >> mWindMaxVelocity;
        file.close();
    }

    void Properties::saveToFile() const
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

    float Properties::getBounceFactor() const
    {
        return mBounceFactor;
    }

    float Properties::getCheckCollisionDistance() const
    {
        return mCheckCollisionDistance;
    }

    float Properties::getFallVelocity() const
    {
        return mFallVelocity;
    }

    float Properties::getFriction() const
    {
        return mFriction;
    }

    float Properties::getGravity() const
    {
        return mGravity;
    }

    float Properties::getWindFactor() const
    {
        return mWindFactor;
    }

    float Properties::getWindMaxVelocity() const
    {
        return mWindMaxVelocity;
    }

    void Properties::setBounceFactor(float bounceFactor)
    {
        mBounceFactor = bounceFactor;
    }

    void Properties::setCheckCollisionDistance(float distance)
    {
        mCheckCollisionDistance = distance;
    }

    void Properties::setFallVelocity(float velocity)
    {
        mFallVelocity = velocity;
    }

    void Properties::setFriction(float friction)
    {
        mFriction = friction;
    }

    void Properties::setGravity(float gravity)
    {
        mGravity = gravity;
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