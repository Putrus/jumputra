#pragma once

namespace jp::game::physics
{
    class Properties
    {
    public:
        Properties(float gravity, float checkCollisionDistance,
            float bounceFactor, float windFactor, float windMaxVelocity);

        float getGravity() const;
        float getCheckCollisionDistance() const;
        float getBounceFactor() const;
        float getWindFactor() const;
        float getWindMaxVelocity() const;

        void setGravity(float gravity);
        void setCheckCollisionDistance(float checkCollisionDistance);
        void setBounceFactor(float bounceFactor);
        void setWindFactor(float windFactor);
        void setWindMaxVelocity(float windMaxVelocity);

    private:
        float mGravity;
        float mCheckCollisionDistance;
        float mBounceFactor;
        float mWindFactor;
        float mWindMaxVelocity;
    };
}