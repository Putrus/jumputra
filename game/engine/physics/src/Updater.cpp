#include "../inc/Updater.hpp"

namespace jp::game::engine::physics
{
    Updater::Updater(const PhysicsProperties& properties) : mProperties(properties)
    {}

    const PhysicsProperties& Updater::getProperties() const
    {
        return mProperties;
    }
}