#include "../inc/Entity.hpp"

namespace jp::game::physics
{
    Entity::Entity(const math::Rect<float>& rect,
        const math::Vector2<float>& velocity, const math::Vector2<float>& acceleration)
        : mRect(rect), Kinematics(velocity, acceleration)
        {}

    void Entity::move(const math::Vector2<float>& vec)
    {
        mRect += vec;
    }

    const math::Rect<float>& Entity::getRect() const
    {
        return mRect;
    }

    math::Vector2<float> Entity::getPosition() const
    {
        return mRect.getPosition();
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