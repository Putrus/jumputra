#include "../inc/PhysicsProperties.hpp"

namespace jp::game::physics
{
    PhysicsProperties::PhysicsProperties()
    {}

    PhysicsProperties::PhysicsProperties(float bounce, float collision, float fall,
        float friction, float gravity, const WindProperties& windProperties)
        : bounceFactor(bounce), checkCollisionDistance(collision), fallVelocity(fall),
            friction(friction), gravity(gravity), wind(windProperties)
    {}
}