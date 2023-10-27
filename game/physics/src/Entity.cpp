#include "../inc/Entity.hpp"

namespace jp::game::physics
{
    Entity::Entity()
    {}

    Entity::Entity(const math::Rect<float>& rect)
        : mRect(rect)
    {}

    void Entity::move(const math::Vector2<float>& vec)
    {
        mRect += vec;
    }

    math::Vector2<float> Entity::getPosition() const
    {
        return mRect.getPosition();
    }

    const math::Rect<float>& Entity::getRect() const
    {
        return mRect;
    }

    float Entity::getRunVelocity() const
    {
        return mRunVelocity;
    }

    EntityState Entity::getState() const
    {
        return mState;
    }

    void Entity::setPosition(const math::Vector2<float>& position)
    {
        mRect.setPosition(position);
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

    void Entity::setRunVelocity(float runVelocity)
    {
        mRunVelocity = runVelocity;
    }

    void Entity::setState(EntityState state)
    {
        mState = state;
    }  
}