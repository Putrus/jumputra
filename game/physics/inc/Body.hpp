#pragma once

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    class Body
    {
    public:
        void update(float dt);

        const math::Rect<float>& getRect() const;

    private:
        void updatePosition(float dt);
        void updateVelocity(float dt);

        math::Rect<float> mRect;
        math::Vector2<float> mVelocity;
        math::Vector2<float> mAcceleration;
    };
}