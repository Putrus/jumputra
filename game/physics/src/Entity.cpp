#include "../inc/Entity.hpp"

namespace jp::game::physics
{
   Entity::Entity() {}

   Entity::Entity(const math::Rect<float>& rect,
      const math::Vector2<float>& acceleration/* = 0.f*/,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : mRect(rect), mAcceleration(acceleration), mVelocity(velocity) {}

   math::Vector2<float> Entity::getPosition() const
   {
      return mRect.getPosition();
   }

   const math::Rect<float>& Entity::getRect() const
   {
      return mRect;
   }

   const math::Vector2<float>& Entity::getAcceleration() const
   {
      return mAcceleration;
   }

   const math::Vector2<float>& Entity::getVelocity() const
   {
      return mVelocity;
   }

   void Entity::setPosition(float x, float y)
   {
      mRect.setPosition(x, y);
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

   void Entity::setAcceleration(const math::Vector2<float>& acceleration)
   {
      mAcceleration = acceleration;
   }

   void Entity::setAccelerationX(float x)
   {
      mAcceleration.x = x;
   }

   void Entity::setAccelerationY(float y)
   {
      mAcceleration.y = y;
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