#pragma once

#include "Character.hpp"
#include "Platform.hpp"
#include "Properties.hpp"
#include "Wind.hpp"

#include <memory>

namespace jp::game::physics
{
    class CharacterUpdater final
    {
    public:
        CharacterUpdater(const Properties& properties);

        void handlePlatformCollision(const Platform& platform);
        void handleNoCollision();

        void update();
        void updatePosition(float dt, const Wind* wind = nullptr);
        void updateVelocity(float dt, const Wind* wind = nullptr);

        const Character& getUpdatedEntity() const;

        void setEntity(std::shared_ptr<Character> entity);

    private:
        void sideBounce();
        void topBounce();
        void topBottomCollision(bool top, PlatformSurface platformSurface);

        void leftPlatformCollision(float x);
        void rightPlatformCollision(float x);
        void topPlatformCollision(float y, PlatformSurface platformSurface);
        void bottomPlatformCollision(float y, PlatformSurface platformSurface);

        math::Vector2<float> getResultantAcceleration(const Character& entity, const Wind* wind = nullptr) const;
        math::Vector2<float> getResultantVelocity(const Character& entity) const;

        std::shared_ptr<Character> mEntity;
        Character mUpdatedEntity;

        const Properties& mProperties;
    };
}