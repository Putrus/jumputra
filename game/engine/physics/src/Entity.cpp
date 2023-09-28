#include "../inc/Entity.hpp"

namespace jp::game::engine::physics
{
    Entity::Entity()
    {}

    Entity::Entity(const math::Rect<float>& rect)
        : mRect(rect)
    {}

    void Entity::setPosition(const math::Vector2<float>& position)
    {
        mRect.setPosition(position);
    }

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

    float Entity::getSlideAcceleration() const
    {
        return mSlideAcceleration;
    }

    float Entity::getSlideVelocity() const
    {
        return mSlideVelocity;
    }

    EntityState Entity::getState() const
    {
        return mState;
    }

    const math::Vector2<float>& Entity::getVelocity() const
    {
        return mVelocity;
    }

    float Entity::getVelocityXSign() const
    {
        return mVelocity.x / std::abs(mVelocity.x);
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

    void Entity::setSlideAcceleration(float acceleration)
    {
        mSlideAcceleration = acceleration;
    }

    void Entity::setSlideVelocity(float velocity)
    {
        mSlideVelocity = velocity;
    }

    void Entity::setState(EntityState state)
    {
        mState = state;
    }

    void Entity::setVelocity(const math::Vector2<float>& velocity)
    {
        mVelocity = velocity;
    }

    void Entity::setVelocityX(float x)
    {
        mVelocity.x = x;
    }

    void Entity::setVelocityY(float y)
    {
        mVelocity.y = y;
    }
}