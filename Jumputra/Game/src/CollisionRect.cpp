#include "../inc/CollisionRect.h"

namespace jp::game
{
   CollisionRect::CollisionRect()
   {
   }

   void CollisionRect::update(sf::Time& dt)
   {
      mSpeed.x = mSpeed.x + mAcceleration.x * dt.asMilliseconds();
      mSpeed.y = mSpeed.y + mAcceleration.y * dt.asMilliseconds();
   }

   sf::Vector2f CollisionRect::getPosition() const
   {
      return sf::Vector2f(mRect.left, mRect.top);
   }

   void CollisionRect::setPosition(const sf::Vector2f& position)
   {
      mRect.left = position.x;
      mRect.top = position.y;
   }
}