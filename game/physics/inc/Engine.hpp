#pragma once

#include "Entity.hpp"
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
        void updateEntity(float dt, Entity& entity) const;

        void updateWind(float dt);

        float mGravity;
        float mCheckCollisionDistance;
        float mBounceFactor;
        float mWindFactor;
        std::shared_ptr<Wind> mWind;
        std::vector<std::shared_ptr<Entity>> mEntities;
        std::vector<std::shared_ptr<Platform>> mPlatforms;
    };
}