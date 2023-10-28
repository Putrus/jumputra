#include "../inc/WindUpdater.hpp"

namespace jp::game::physics
{
    WindUpdater::WindUpdater(std::shared_ptr<Wind> wind, const WindProperties& properties)
        : mWind(wind), Updater<WindProperties>(properties)
    {}

    void WindUpdater::update(float dt)
    {   
        //wind update implemented only for x axis
        if (getProperties().maxVelocity == 0.f)
        {
            return;
        }
        mWind->setVelocity(mWind->getVelocity() + mWind->getAcceleration() * dt);
        float absVelocity = std::abs(mWind->getVelocity().x);
        if (absVelocity >= getProperties().maxVelocity)
        {
            float velocitySign = mWind->getVelocity().x / absVelocity;
            mWind->setVelocity(getProperties().maxVelocity * velocitySign);
            mWind->setAcceleration(getProperties().acceleration * -velocitySign);
        }
    }
}