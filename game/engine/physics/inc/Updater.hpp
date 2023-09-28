#pragma once

#include "PhysicsProperties.hpp"

namespace jp::game::engine::physics
{
    class Updater
    {
    public:
        Updater(const PhysicsProperties& properties);

        const PhysicsProperties& getProperties() const;

    private:
        const PhysicsProperties& mProperties;
    };
}