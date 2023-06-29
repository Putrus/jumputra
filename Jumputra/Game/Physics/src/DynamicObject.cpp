#include "../inc/DynamicObject.h"

namespace jp::game::physics
{
   bool DynamicObject::update(const sf::Time& dt, const std::vector<StaticObject>& objects)
   {
      sf::Vector2f newPosition = this->getPosition();
      float t = dt.asMilliseconds();
      newPosition.x += mVelocity.x * t + (mAcceleration.x * t * t) / 2.f;
      newPosition.y += mVelocity.y * t + (mAcceleration.y * t * t) / 2.f;
      for (const StaticObject& object : objects)
      {
         //check collision
         if (newPosition.x + getRect().width >= object.getPosition().x &&
            object.getPosition().x + object.getRect().width >= newPosition.x &&
            newPosition.y + getRect().height >= object.getPosition().y &&
            object.getPosition().y + object.getRect().height >= newPosition.y)
         {
            mAcceleration.x *= -1.f;
            mAcceleration.y *= -1.f;
            mVelocity.x *= -1.f;
            mVelocity.y *= -1.f;
         }
      }
      mVelocity.x = mVelocity.x + mAcceleration.x * t;
      mVelocity.y = mVelocity.y + mAcceleration.y * t;
      return true;
   }
}