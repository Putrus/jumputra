#pragma once

#include "Entity.hpp"
#include "Updater.hpp"

#include <memory>

namespace jp::game::physics
{
    class EntityUpdater : public Updater
    {
    public:
        EntityUpdater(std::shared_ptr<Entity> entity, const Properties& properties);

        void updatePosition(float dt);
        void updateVelocity(float dt);

    private:
        std::shared_ptr<Entity> mEntity;
        Entity mUpdatedEntity;
    };
}