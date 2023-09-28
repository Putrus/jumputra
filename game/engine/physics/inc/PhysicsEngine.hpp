#pragma once

#include "EntityUpdater.hpp"
#include "Platform.hpp"
#include "Properties.hpp"
#include "WindUpdater.hpp"

#include <map>
#include <memory>
#include <vector>

namespace jp::game::physics
{
    class Engine
    {
    public:
        Engine(Properties&& properties, std::vector<std::shared_ptr<Entity>>&& entities,
            std::vector<std::shared_ptr<Platform>>&& platforms, std::shared_ptr<Wind>&& wind);

        void update(float dt);

    private:
        void updateEntities(float dt);
        void updateWind(float dt);

        Properties mProperties;

        std::vector<std::shared_ptr<Entity>> mEntities;
        std::vector<std::shared_ptr<Platform>> mPlatforms;
        std::shared_ptr<Wind> mWind;

        EntityUpdater mEntityUpdater;
        WindUpdater mWindUpdater;
    };
}