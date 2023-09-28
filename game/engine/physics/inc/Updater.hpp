#pragma once

#include "Properties.hpp"

#include <memory>

namespace jp::game::engine::physics
{
    class Updater
    {
    public:
        Updater(const jp::game::engine::physics::Properties& properties);

        const jp::game::engine::physics::Properties& getProperties() const;

    private:
        const jp::game::engine::physics::Properties& mProperties;
    };
}