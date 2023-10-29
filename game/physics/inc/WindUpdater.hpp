#pragma once

#include "Wind.hpp"

#include <memory>

namespace jp::game::physics
{
    class WindUpdater final
    {
    public:
        void update(float dt);

        void setWind(const std::shared_ptr<Wind>& wind);

    private:
        std::shared_ptr<Wind> mWind;
    };
}