#pragma once

#include "Wind.hpp"

#include "../../math/inc/Vector2.hpp"

namespace jp::game::physics
{
    class Parameters
    {
    public:
        Parameters(float bounce, float gravity, const math::Vector2<float>& maxVelocity, std::shared_ptr<UpdatableWind> wind);

        float getCheckCollisionDistance() const;
        float getBounce() const;
        float getGravity() const;
        const math::Vector2<float>& getMaxVelocity() const;
        const Wind& getWind() const;

    protected:
        float mBounce;
        float mGravity;
        float mCheckCollisionDistance;
        math::Vector2<float> mMaxVelocity;
        std::shared_ptr<UpdatableWind> mWind;
    };

    class UpdatableParameters final : public Parameters
    {
    public:
        void update(float dt);
    };
}