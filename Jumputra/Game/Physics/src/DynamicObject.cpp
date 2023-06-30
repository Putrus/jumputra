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
         if (newRect.intersects(object.getRect()))
         {
            sf::Vector2f center1(newRect.left + newRect.width / 2.f, newRect.top + newRect.height / 2.f);
            sf::Vector2f center2(object.getRect().left + object.getRect().width / 2.f, object.getRect().top + object.getRect().height / 2.f);

            sf::Vector2f difference = center2 - center1;
            sf::Vector2f direction(0.0f, 0.0f);

            float xOverlap = (newRect.width + object.getRect().width) / 2.f - std::abs(difference.x);
            float yOverlap = (newRect.height + object.getRect().height) / 2.f - std::abs(difference.y);

            if (xOverlap <= yOverlap)
            {
               if (difference.x > 0)
               {
                  direction.x = -1.0f;
               }
               else {
                  direction.x = 1.0f;
               }
            }
            else {
               if (difference.y > 0) {
                  direction.y = -1.0f;
               }
               else {
                  direction.y = 1.0f;
               }
            }

            if (direction.y == -1.0f)
            {
               newRect.top = object.getRect().top - newRect.height;
               mVelocity.y = 0.f;
               ret = false;
               break;
            }
            else if (direction.y == 1.0f)
            {
               mVelocity.y *= -1.f;
               collision = true;
               break;
            }
            else if (direction.x != 0.0f)
            {
               mVelocity.x *= -1.f;
               collision = true;
               break;
            }
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