#include "../inc/Engine.hpp"

namespace jp::game::physics
{
    Engine::Engine(Properties&& properties, std::vector<std::shared_ptr<Entity>>&& entities,
        std::vector<std::shared_ptr<Platform>>&& platforms, std::shared_ptr<Wind>&& wind)
        : mProperties(properties), mEntities(entities), mPlatforms(platforms), mWind(wind),
            mEntityUpdater(mProperties, *mWind), mWindUpdater(mWind, mProperties)
    {}
    
    void Engine::update(float dt)
    {
        updateWind(dt);
        updateEntities(dt);
    }

    void Engine::updateEntities(float dt)
    {
        for (auto& entity : mEntities)
        {
            mEntityUpdater.setEntity(entity);
            mEntityUpdater.updatePosition(dt);
            mEntityUpdater.updateVelocity(dt);
            for (const auto& platform : mPlatforms)
            {
                if (platform->getSegment().a.y > mEntityUpdater.getUpdatedEntity().getPosition().y + mProperties.getCheckCollisionDistance())
                {
                    continue;
                }

                if (platform->getSegment().a.y < mEntityUpdater.getUpdatedEntity().getPosition().y - mProperties.getCheckCollisionDistance())
                {
                    break;
                }
                mEntityUpdater.handlePlatformCollision(*platform);
            }
            mEntityUpdater.update();
        }
    }

    void Engine::updateWind(float dt)
    {
        mWindUpdater.update(dt);
    }
}