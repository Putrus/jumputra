#include "../inc/WindUpdater.hpp"

namespace jp::game::physics
{
    WindUpdater::WindUpdater(std::shared_ptr<Wind> wind, const Properties& properties)
    : mWind(wind), Updater(properties)
    {}

    void WindUpdater::update(float dt)
    {
        mWind->setVelocity(mWind->getVelocity() + mWind->getAcceleration() * dt);
        float absVelocity = std::abs(mWind->getVelocity());
        if (absVelocity >= getProperties().getWindMaxVelocity())
        {
            mWind->setVelocity(getProperties().getWindMaxVelocity() * (mWind->getVelocity() / absVelocity));
            mWind->setAcceleration(mWind->getAcceleration() * -1.f);
        }
    }
}