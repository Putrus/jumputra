#include "../inc/Body.hpp"

namespace jp::game::physics
{
    void Body::update(float dt)
    {
        Body newBody = *this;
        newBody.updateVelocity(dt);
        newBody.updatePosition(dt);
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