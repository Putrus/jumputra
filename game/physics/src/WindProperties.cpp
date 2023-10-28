#include "../inc/WindProperties.hpp"

namespace jp::game::physics
{
    WindProperties::WindProperties()
    {}

    WindProperties::WindProperties(float acceleration, float factor, float maxVelocity,
        float startPosition, float endPosition)
        : acceleration(acceleration), factor(factor), maxVelocity(maxVelocity),
        startPosition(startPosition), endPosition(endPosition)
    {}
}