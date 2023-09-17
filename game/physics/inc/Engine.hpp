#pragma once

#include "Body.hpp"
#include "Platform.hpp"
#include "Wind.hpp"

#include <map>
#include <memory>
#include <vector>

namespace jp::game::physics
{
    class Engine
    {
    public:
        void update(float dt);

    private:
        float mBounce;
        float mGravity;
        std::shared_ptr<Wind> mWind;
        std::vector<std::shared_ptr<Body>> mBodies;
    };
}