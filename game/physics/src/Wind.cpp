#include "../inc/Wind.hpp"

namespace jp::game::physics
{
    Wind::Wind() : Kinematics()
    {}
    
    Wind::Wind(const WindProperties& windProperties)
        : mStartPosition(windProperties.startPosition),
        mEndPosition(windProperties.endPosition),
        Kinematics(math::Vector2<float>(windProperties.acceleration, 0.f), 0.f)
    {}

    float Wind::getStartPosition() const
    {
        return mStartPosition;
    }

    float Wind::getEndPosition() const
    {
        return mEndPosition;
    }
}