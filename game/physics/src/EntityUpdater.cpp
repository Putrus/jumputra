#include "../inc/EntityUpdater.hpp"

namespace jp::game::physics
{
    EntityUpdater::EntityUpdater(std::shared_ptr<Entity> entity, const Properties& properties)
    : mEntity(entity), mUpdatedEntity(*entity), Updater(properties)
    {}

    void EntityUpdater::updatePosition(float dt)
    {

    }

    void EntityUpdater::updateVelocity(float dt)
    {
        mUpdatedEntity.setVelocity(mUpdatedEntity.getVelocity() +
            (mUpdatedEntity.getAcceleration() + math::Vector2<float>(0.f, getProperties().getGravity())) * dt);
    }

}