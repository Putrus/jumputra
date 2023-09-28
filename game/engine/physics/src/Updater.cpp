#include "../inc/Updater.hpp"

namespace jp::game::engine::physics
{
    Updater::Updater(const jp::game::engine::physics::Properties& properties) : mProperties(properties)
    {}

    const jp::game::engine::physics::Properties& Updater::getProperties() const
    {
        return mProperties;
    }
}