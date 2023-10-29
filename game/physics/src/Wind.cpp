#include "../inc/Wind.hpp"

namespace jp::game::physics
{
    Wind::Wind()
    {}
    
    Wind::Wind(float acceleration, float factor,
        float maxVelocity, const math::Rect<float>& rect)
        : mFactor(factor), mMaxVelocity(maxVelocity),
        Entity(rect, math::Vector2<float>(acceleration, 0.f), math::Vector2<float>())
    {}

    float Wind::getFactor() const
    {
        return mFactor;
    }

    float Wind::getMaxVelocity() const
    {
        return mMaxVelocity;
    }
}