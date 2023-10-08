#pragma once

#include "Entity.hpp"
#include "Platform.hpp"
#include "Updater.hpp"
#include "Wind.hpp"

#include <memory>

namespace jp::game::engine::physics
{
    class EntityUpdater : public Updater
    {
    public:
        EntityUpdater(const PhysicsProperties& properties, const Wind& wind);

        void handlePlatformCollision(const Platform* platform);

        void update();
        void updatePosition(float dt);
        void updateVelocity(float dt);

        const Entity& getUpdatedEntity() const;

        void setEntity(std::shared_ptr<Entity> entity);

    private:
        void bounce();
        void leftPlatformCollision(float x);
        void rightPlatformCollision(float x);

        void land(bool top, PlatformSurface platformSurface);
        void topPlatformCollision(float y, PlatformSurface platformSurface);
        void bottomPlatformCollision(float y, PlatformSurface platformSurface);

        math::Vector2<float> getResultantAcceleration(const Entity& entity) const;
        math::Vector2<float> getResultantVelocity(const Entity& entity) const;

        std::shared_ptr<Entity> mEntity;
        Entity mUpdatedEntity;
        const Wind& mWind;
    };
}