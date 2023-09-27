#pragma once

namespace jp::game::physics
{
    class Properties
    {
    public:
        Properties();

        void loadFromFile();
        void saveToFile() const;

        float getBounceFactor() const;
        float getCheckCollisionDistance() const;
        float getFallVelocity() const;
        float getFriction() const;
        float getGravity() const;
        float getWindFactor() const;
        float getWindMaxVelocity() const;

        void setBounceFactor(float bounceFactor);
        void setCheckCollisionDistance(float distance);
        void setFallVelocity(float velocity);
        void setFriction(float friction);
        void setGravity(float gravity);
        void setWindFactor(float windFactor);
        void setWindMaxVelocity(float windMaxVelocity);

    private:
        float mBounceFactor;
        float mCheckCollisionDistance;
        float mFallVelocity;
        float mFriction;
        float mGravity;
        float mWindFactor;
        float mWindMaxVelocity;
    };
}