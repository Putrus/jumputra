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
        PhysicsEngine(const PhysicsProperties& properties, std::vector<std::shared_ptr<Platform>>&& platforms,
            std::shared_ptr<Wind>&& wind, std::vector<std::shared_ptr<Entity>>&& entities = std::vector<std::shared_ptr<Entity>>());

        void addEntity(const std::shared_ptr<Entity>& entity);
        void addEntity(std::shared_ptr<Entity>&& entity);
        void update(float dt);

        const std::vector<std::shared_ptr<Platform>>& getPlatforms() const;
        const std::shared_ptr<Wind>& getWind() const;

    private:
        void updateEntities(float dt);
        void updateWind(float dt);

        const PhysicsProperties& mProperties;

        std::vector<std::shared_ptr<Entity>> mEntities;
        std::vector<std::shared_ptr<Platform>> mPlatforms;
        std::shared_ptr<Wind> mWind;

        EntityUpdater mEntityUpdater;
        WindUpdater mWindUpdater;
    };
}