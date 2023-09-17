#include "../inc/Body.hpp"

namespace jp::game::physics
{
    void Body::update(float dt)
    {
        Body newBody = *this;
    }

    const math::Rect<float>& Body::getRect() const
    {
        return mRect;
    }

    void Body::updatePosition(float dt)
    {

    }

    void Body::updateVelocity(float dt)
    {
    }
}