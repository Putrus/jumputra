#pragma once

#include "Entity.hpp"
#include "Platform.hpp"
#include "Updater.hpp"
#include "Wind.hpp"

#include <memory>

namespace jp::game::physics
{
    class EntityUpdater : public Updater<PhysicsProperties>
    {
    public:
        EntityUpdater(const PhysicsProperties& properties);

        void handlePlatformCollision(const Platform& platform);
        void handleNoCollision();

        void update();
        void updatePosition(float dt, const Wind& wind);
        void updateVelocity(float dt, const Wind& wind);

        const Entity& getUpdatedEntity() const;

        void setEntity(std::shared_ptr<Entity> entity);

    private:
        void sideBounce();
        void topBounce();
        void topBottomCollision(bool top, PlatformSurface platformSurface);

        void leftPlatformCollision(float x);
        void rightPlatformCollision(float x);
        void topPlatformCollision(float y, PlatformSurface platformSurface);
        void bottomPlatformCollision(float y, PlatformSurface platformSurface);

        math::Vector2<float> getResultantAcceleration(const Entity& entity, const Wind& wind) const;
        math::Vector2<float> getResultantVelocity(const Entity& entity) const;

        std::shared_ptr<Entity> mEntity;
        Entity mUpdatedEntity;
    };
}