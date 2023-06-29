#include "../inc/StaticObject.h"

namespace jp::game::physics
{
   sf::FloatRect StaticObject::getRect() const
   {
      return mRect;
   }

   sf::Vector2f StaticObject::getPosition() const
   {
      return sf::Vector2f(mRect.left, mRect.top);
   }

   void StaticObject::setPosition(const sf::Vector2f& position)
   {
      mRect.left = position.x;
      mRect.top = position.y;
   }

   void StticObject::setSize(const sf::Vector2f& size)
   {
      mRect.width = size.x;
      mRect.height = size.y;
   }

   void StaticObject::setRect(const sf::FloatRect& rect)
   {
      mRect = rect;
   }
}