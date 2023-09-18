#include "../inc/Wind.hpp"

#include <cmath>

namespace jp::game::physics
{
    Wind::Wind(const math::Vector2<float>& maxVelocity, const math::Vector2<float>& acceleration,
        const math::Vector2<float>& velocity/* = math::Vector2<float>()*/)
        : mMaxVelocity(maxVelocity), Kinematics(acceleration, velocity)
    {}

    const math::Vector2<float>& Wind::getMaxVelocity() const
    {
        return mMaxVelocity;
    }

    void Wind::setMaxVelocity(const math::Vector2<float>& velocity)
    {
        mMaxVelocity = velocity;
    }

}