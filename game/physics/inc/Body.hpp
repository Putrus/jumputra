#pragma once

#include "Parameters.hpp"
#include "Platform.hpp"

#include "../../math/inc/Rect.hpp"

#include <vector>

namespace jp::game::physics
{
    class Body
    {
    public:
        Body(const math::Rect<float>& rect, const math::Vector2<float>& velocity = math::Vector2<float>(0.f, 0.f),
            const math::Vector2<float>& acceleration = math::Vector2<float>(0.f, 0.f));
        const math::Rect<float>& getRect() const;

    protected:
        math::Rect<float> mRect;
        math::Vector2<float> mVelocity;
        math::Vector2<float> mAcceleration;

        setAcceleration({Wind, gravity});
        mVelocity = mVelocity + mAcceleration + { Wind, Gravity } * dt;
    };

    class UpdatableBody final : public Body
    {
    public:
        void update(float dt);
        //setters
        //getters

    private:
        void updateRect(float dt);
        void updateVelocity(float dt);
    };
}