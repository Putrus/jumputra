#include "../inc/Parameters.hpp"

namespace jp::game::physics
{
    Parameters::Parameters(float bounce, float gravity, const math::Vector2<float>& maxVelocity, std::shared_ptr<UpdatableWind> wind)
    : mBounce(bounce), mGravity(gravity), mMaxVelocity(maxVelocity), mWind(wind)
    {}

    float Parameters::getCheckCollisionDistance() const
    {
        return mCheckCollisionDistance;
    }

    float Parameters::getBounce() const
    {
        return mBounce;
    }

    float Parameters::getGravity() const
    {
        return mGravity;
    }


    const math::Vector2<float>& Parameters::getMaxVelocity() const
    {
        return mMaxVelocity;
    } 

    const Wind& Parameters::getWind() const
    {
        return *mWind;
    }

    void UpdatableParameters::update(float dt)
    {
        mWind->update(dt);
    }
}