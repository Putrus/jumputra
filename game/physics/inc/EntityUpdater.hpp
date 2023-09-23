#pragma once

#include "Entity.hpp"
#include "Platform.hpp"
#include "Updater.hpp"
#include "Wind.hpp"

#include <memory>

namespace jp::game::physics
{
    class EntityUpdater : public Updater
    {
    public:
        EntityUpdater(std::shared_ptr<Entity> entity, const Properties& properties, const Wind& wind);

        void handlePlatformCollision(const Platform& platform);

        void updatePosition(float dt);
        void updateVelocity(float dt);

        void setEntity(std::shared_ptr<Entity> entity);

    private:
        void bounce();
        void bounceLeft(float x);
        void bounceRight(float x);

        std::shared_ptr<Entity> mEntity;
        Entity mUpdatedEntity;
        const Wind& mWind;
    };
}