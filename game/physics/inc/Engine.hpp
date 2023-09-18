#pragma once

#include "KinematicRect.hpp"
#include "Parameters.hpp"
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
        std::shared_ptr<UpdatableParameters> mParameters;
        std::vector<std::shared_ptr<UpdatableBody>> mBodies;
    };
}