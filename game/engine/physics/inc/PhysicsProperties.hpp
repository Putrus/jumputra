#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::engine::physics
{
    class PhysicsProperties
    {
    public:
        PhysicsProperties();
        PhysicsProperties(float bounce, float collision, float fall,
            float friction, float gravity, float windFactor, float windMaxVelocity);

        void loadFromFile();
        void saveToFile() const;

        float getBounceFactor() const;
        float getCheckCollisionDistance() const;
        float getFallVelocity() const;
        float getFriction() const;
        float getGravity() const;
        float getWindFactor() const;
        const math::Vector2<float>& getWindAcceleration() const;
        const math::Vector2<float>& getWindMaxVelocity() const;

        void setBounceFactor(float bounceFactor);
        void setCheckCollisionDistance(float distance);
        void setFallVelocity(float velocity);
        void setFriction(float friction);
        void setGravity(float gravity);
        void setWindFactor(float windFactor);
        void setWindAcceleration(const math::Vector2<float>& windAcceleration);
        void setWindMaxVelocity(const math::Vector2<float>& windMaxVelocity);

    private:
        float mBounceFactor;
        float mCheckCollisionDistance;
        float mFallVelocity;
        float mFriction;
        float mGravity;
        float mWindFactor;
        math::Vector2<float> mWindAcceleration;
        math::Vector2<float> mWindMaxVelocity;
    };
}