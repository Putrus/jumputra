#include "../inc/Updater.hpp"

namespace jp::game::physics
{
    Updater::Updater(const Properties& properties) : mProperties(properties)
    {}

    const Properties& Updater::getProperties() const
    {
        return mProperties;
    }
}