#pragma once

#include "KinematicRect.hpp"
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
    };
}