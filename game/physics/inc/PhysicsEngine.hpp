#pragma once

#include "EntityUpdater.hpp"
#include "Platform.hpp"
#include "WindUpdater.hpp"

#include <map>
#include <memory>
#include <vector>

namespace jp::game::physics
{
    class PhysicsEngine
    {
    public:
        PhysicsEngine(PhysicsProperties&& properties, std::vector<std::shared_ptr<Entity>>&& entities,
            std::vector<std::shared_ptr<Platform>>&& platforms, std::shared_ptr<Wind>&& wind);

        void update(float dt);
        const std::vector<std::shared_ptr<Platform>>& getPlatforms() const;

    private:
        void updateEntities(float dt);
        void updateWind(float dt);

        PhysicsProperties mProperties;

        std::vector<std::shared_ptr<Entity>> mEntities;
        std::vector<std::shared_ptr<Platform>> mPlatforms;
        std::shared_ptr<Wind> mWind;

        EntityUpdater mEntityUpdater;
        WindUpdater mWindUpdater;
    };
}