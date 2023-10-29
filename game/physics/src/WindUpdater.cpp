#include "../inc/WindUpdater.hpp"

namespace jp::game::physics
{
    void WindUpdater::update(float dt)
    {   
        //wind update implemented only for x axis
        if (mWind->getMaxVelocity() == 0.f)
        {
            return;
        }
        mWind->setVelocity(mWind->getVelocity() + mWind->getAcceleration() * dt);
        float absVelocity = std::abs(mWind->getVelocity().x);
        if (absVelocity >= mWind->getMaxVelocity())
        {
            float velocitySign = mWind->getVelocity().x / absVelocity;
            mWind->setVelocity(math::Vector2<float>(mWind->getMaxVelocity() * velocitySign, 0.f));
            mWind->setAcceleration(math::Vector2<float>(mWind->getAcceleration().x * -velocitySign, 0.f));
        }
    }

    void WindUpdater::setWind(const std::shared_ptr<Wind>& wind)
    {
        mWind = wind;
    }
}