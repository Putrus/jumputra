#include "../inc/PhysicsEngine.hpp"

namespace jp::game::physics
{
    PhysicsEngine::PhysicsEngine(const PhysicsProperties& properties, std::vector<std::shared_ptr<Platform>>&& platforms,
        std::shared_ptr<Wind>&& wind, std::vector<std::shared_ptr<Entity>>&& entities/* = std::vector<std::shared_ptr<Entity>>()*/)
        : mProperties(properties), mPlatforms(platforms), mWind(wind), mEntities(entities),
            mEntityUpdater(mProperties, *mWind), mWindUpdater(mWind, mProperties)
    {}

    void PhysicsEngine::addEntity(const std::shared_ptr<Entity>& entity)
    {
        mEntities.push_back(entity);
    }

    void PhysicsEngine::addEntity(std::shared_ptr<Entity>&& entity)
    {
        mEntities.push_back(std::move(entity));
    }
    
    void PhysicsEngine::update(float dt)
    {
        updateWind(dt);
        updateEntities(dt);
    }

    const std::vector<std::shared_ptr<Platform>>& PhysicsEngine::getPlatforms() const
    {
        return mPlatforms;
    }

    void PhysicsEngine::updateEntities(float dt)
    {
        for (auto entityIt = mEntities.begin(); entityIt != mEntities.end(); ++entityIt)
        {
            mEntityUpdater.setEntity(*entityIt);
            //remove entity if it only exists in the physics engine
            if (entityIt->use_count() == 2)
            {
                entityIt = --mEntities.erase(entityIt);
            }
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
                mEntityUpdater.handlePlatformCollision(platform.get());
            }
            mEntityUpdater.update();
        }
    }

    void PhysicsEngine::updateWind(float dt)
    {
        mWindUpdater.update(dt);
    }
}