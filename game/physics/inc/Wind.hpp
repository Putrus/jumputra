#pragma once

#include "Entity.hpp"

namespace jp::game::physics
{
    class Wind final : public Entity
    {
    public:
        Wind();
        Wind(float acceleration, float factor,
            float maxVelocity, const math::Rect<float>& rect);

        float getFactor() const;
        float getMaxVelocity() const;

    private:
        float mFactor = 0.f;
        float mMaxVelocity = 0.f;
    };
}