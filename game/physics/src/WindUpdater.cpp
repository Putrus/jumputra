#include "../inc/WindUpdater.hpp"

namespace jp::game::physics
{
    WindUpdater::WindUpdater(std::shared_ptr<Wind> wind, const PhysicsProperties& properties)
    : mWind(wind), Updater(properties)
    {}

    void WindUpdater::update(float dt)
    {   
        //wind update implemented only for x axis
        if (getProperties().getWindMaxVelocity().x == 0.f)
        {
            return;
        }
        mWind->setVelocity(mWind->getVelocity() + mWind->getAcceleration() * dt);
        float absVelocity = std::abs(mWind->getVelocity().x);
        if (absVelocity >= getProperties().getWindMaxVelocity().x)
        {
            float velocitySign = mWind->getVelocity().x / absVelocity;
            mWind->setVelocity(getProperties().getWindMaxVelocity() * velocitySign);
            mWind->setAcceleration(getProperties().getWindAcceleration() * -velocitySign);
        }
    }
}