#pragma once

#include "Updater.hpp"
#include "Wind.hpp"

namespace jp::game::physics
{
    class WindUpdater final : public Updater
    {
    public:
        WindUpdater(std::shared_ptr<Wind> wind, const Properties& properties);

        void update(float dt);

    private:
        std::shared_ptr<Wind> mWind;
    };
}