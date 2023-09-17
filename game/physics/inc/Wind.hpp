#pragma once

namespace jp::game::physics
{
    class Wind
    {
    public:
        Wind(float acceleration, float maxVelocity, float velocity = 0.f);
        void update(float dt);
        float getVelocity() const;

    private:
        float mAcceleration;
        float mMaxVelocity;
        float mVelocity;
    };  
}