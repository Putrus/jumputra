#include "../inc/DynamicObject.h"

namespace jp::game::physics
{
   DynamicObject::DynamicObject() : mAcceleration(sf::Vector2f(0.f, GRAVITY)) {}

   DynamicObject::DynamicObject(const sf::FloatRect& rect,
      const sf::Vector2f& velocity /*= sf::Vector2f(0.f, 0.f)*/,
      const sf::Vector2f& acceleration /*= sf::Vector2f(0.f, GRAVITY)*/)
      : StaticObject(rect), mVelocity(velocity), mAcceleration(acceleration) {}

   DynamicObject::DynamicObject(const sf::Vector2f& position, const sf::Vector2f& size,
      const sf::Vector2f& velocity /*= sf::Vector2f(0.f, 0.f)*/,
      const sf::Vector2f& acceleration /*= sf::Vector2f(0.f, GRAVITY)*/)
      : StaticObject(position, size), mVelocity(velocity), mAcceleration(acceleration) {}

   void DynamicObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      StaticObject::draw(target, states, sf::Color::Red);
   }

   void DynamicObject::update(const sf::Time& dt, const std::vector<StaticObject>& objects)
   {
      sf::FloatRect newRect = getRect();
      float t = dt.asSeconds();
      newRect.left += mVelocity.x * t + (mAcceleration.x * t * t) / 2.f;
      newRect.top += mVelocity.y * t + (mAcceleration.y * t * t) / 2.f;
      for (const StaticObject& object : objects)
      {
         if (checkCollision(newRect, object))
         {
            break;
         }
      }
      setRect(newRect);
      mVelocity = mVelocity + mAcceleration * t;
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

   bool DynamicObject::checkCollision(sf::FloatRect& newRect, const StaticObject& object)
   {
      if (newRect.intersects(object.getRect()))
      {
         sf::Vector2f newRectCenter(newRect.left + newRect.width / 2.f,
            newRect.top + newRect.height / 2.f);
         sf::Vector2f objectCenter(object.getRect().left + object.getRect().width / 2.f,
            object.getRect().top + object.getRect().height / 2.f);

         sf::Vector2f difference = objectCenter - newRectCenter;
         sf::Vector2f direction(0.0f, 0.0f);

         sf::Vector2f overlap((newRect.width + object.getRect().width) / 2.f - std::abs(difference.x),
            (newRect.height + object.getRect().height) / 2.f - std::abs(difference.y));

         if (overlap.x <= overlap.y)
         {
            direction.x = difference.x > 0.f ? -1.f : 1.f;
         }
         else
         {
            direction.y = difference.y > 0.f ? -mAcceleration.y : mAcceleration.y;
         }

         if (direction.y < 0.f)
         {
            //dynamic object hit or is on the ground
            newRect.top = object.getRect().top - newRect.height;
            mVelocity.y = 0.f;
            return true;
         }
         else if (direction.y > 0.f)
         {
            //dynamic object hit the ceiling/top
            newRect.top = object.getRect().top + object.getRect().height;
            mVelocity.y *= -1.f;
            return true;
         }
         else if (direction.x != 0.0f)
         {
            //dynamic object hit the wall to the left or right
            newRect.left = direction.x > 0 ? object.getRect().left + object.getRect().width
               : object.getRect().left - newRect.width;
            //if dynamic object is in the air, it bounces, and if it's on the ground, it stops
            mVelocity.x = inAir ? -mVelocity.x : 0.f;
            return true;
         }
         else
         {
            throw std::runtime_error("Failed to check collision, collision direction is { 0, 0 }");
         }
      }
      return false;
   }
}