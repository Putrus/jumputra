#pragma once

#include "Properties.hpp"

#include <memory>

namespace jp::game::physics
{
    class Updater
    {
    public:
        Updater(const Properties& properties);

        const Properties& getProperties() const;

    private:
        const Properties& mProperties;
    };
}