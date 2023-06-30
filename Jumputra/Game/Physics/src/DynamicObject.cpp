#include "../inc/DynamicObject.h"

#include <iostream>

namespace jp::game::physics
{
   DynamicObject::DynamicObject()
   {}

   DynamicObject::DynamicObject(const sf::FloatRect& rect,
      const sf::Vector2f& velocity, const sf::Vector2f& acceleration)
      : StaticObject(rect), mVelocity(velocity), mAcceleration(acceleration)
   {}

   DynamicObject::DynamicObject(const sf::Vector2f& position, const sf::Vector2f& size,
      const sf::Vector2f& velocity, const sf::Vector2f& acceleration)
      : StaticObject(position, size), mVelocity(velocity), mAcceleration(acceleration)
   {}

   bool DynamicObject::update(const sf::Time& dt, const std::vector<StaticObject>& objects)
   {
      sf::FloatRect newRect = getRect();
      float t = dt.asMilliseconds();
      newRect.left += mVelocity.x * t + (mAcceleration.x * t * t) / 2.f;
      newRect.top += mVelocity.y * t + (mAcceleration.y * t * t) / 2.f;
      bool collision = false;
      bool ret = true;
      for (const StaticObject& object : objects)
      {
         //check collision
         if (newRect.intersects(object.getRect()))
         {
            if (newRect.top + newRect.height <= object.getRect().top + 10.f)
            {
               newRect.top = object.getRect().top - newRect.height;
               mVelocity.y = 0.f;
               ret = false;
               break;
            }
            mVelocity.x *= -1.f;
            collision = true;
            break;
         }
      }

      if (!collision)
      {
         setRect(newRect);
      }

      mVelocity.x = mVelocity.x + mAcceleration.x * t;
      mVelocity.y = mVelocity.y + mAcceleration.y * t;
      return ret;
   }

   sf::Vector2f DynamicObject::getVelocity() const
   {
      return mVelocity;
   }

   sf::Vector2f DynamicObject::getAcceleration() const
   {
      return mAcceleration;
   }

   void DynamicObject::setVelocity(const sf::Vector2f& velocity)
   {
      mVelocity = velocity;
   }

   void DynamicObject::setAcceleration(const sf::Vector2f& acceleration)
   {
      mAcceleration = acceleration;
   }
}