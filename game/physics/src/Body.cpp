#include "../inc/Body.hpp"

namespace jp::game::physics
{
    Body::Body(const math::Rect<float>& rect, const math::Vector2<float>& velocity = math::Vector2<float>(0.f, 0.f),
            const math::Vector2<float>& acceleration = math::Vector2<float>(0.f, 0.f))
            : mRect(rect), mAcceleration(acceleration), mVelocity(velocity), 
    {

    }

    const math::Rect<float>& Body::getRect() const
    {
        return mRect;
    }

    void UpdatableBody::update(float dt)
    {
        Body newBody = *this;
    }
}