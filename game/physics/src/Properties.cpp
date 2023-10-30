#include "../inc/Properties.hpp"

namespace jp::game::physics
{
    Properties::Properties()
    {}

    Properties::Properties(float bounce, float collision,
        float fall, float friction, float gravity)
        : bounceFactor(bounce), checkCollisionDistance(collision),
        fallVelocity(fall), friction(friction), gravity(gravity)
    {}
}