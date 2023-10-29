#include "../inc/Entity.hpp"

namespace jp::game::physics
{
    Entity::Entity()
    {}

    Entity::Entity(const math::Rect<float>& rect,
        const math::Vector2<float>& acceleration/* = 0.f*/,
        const math::Vector2<float>& velocity/* = 0.f*/)
        : mRect(rect), Kinematics(acceleration, velocity)
    {}

    math::Vector2<float> Entity::getPosition() const
    {
        return mRect.getPosition();
    }

    const math::Rect<float>& Entity::getRect() const
    {
        return mRect;
    }

    void Entity::setRect(const math::Rect<float>& rect)
    {
        mRect = rect;
    }

    void Entity::setRectTop(float y)
    {
        mRect.top = y;
    }

    void Entity::setRectBottom(float y)
    {
        mRect.top = y - mRect.height;
    }

    void Entity::setRectLeft(float x)
    {
        mRect.left = x;
    }

    void Entity::setRectRight(float x)
    {
        mRect.left = x - mRect.width;
    }
}