#pragma once

namespace jp::game::physics
{
    class Wind
    {
    public:
        Wind(float acceleration, float maxVelocity, float velocity = 0.f);
        float getVelocity() const;

    protected:
        float mAcceleration;
        float mMaxVelocity;
        float mVelocity;
    };  

    class UpdatableWind final : public Wind
    {
    public:
        void update(float dt);
    };
}