#pragma once

#include "Updater.hpp"
#include "Wind.hpp"

#include <memory>

namespace jp::game::physics
{
    class WindUpdater final : public Updater
    {
    public:
        WindUpdater(std::shared_ptr<Wind> wind, const PhysicsProperties& properties);

        void update(float dt);

    private:
        std::shared_ptr<Wind> mWind;
    };
}