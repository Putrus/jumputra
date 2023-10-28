#pragma once

#include "PhysicsProperties.hpp"

namespace jp::game::physics
{
    template <typename T>
    class Updater
    {
    public:
        Updater(const T& properties)
            : mProperties(properties)
        {}

        const T& getProperties() const
        {
            return mProperties;
        }

    private:
        const T& mProperties;
    };
}