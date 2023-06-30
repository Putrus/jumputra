#include "../inc/StaticObject.h"

namespace jp::game::physics
{
   StaticObject::StaticObject()
   {}

   StaticObject::StaticObject(const sf::FloatRect& rect) : mRect(rect)
   {}

   StaticObject::StaticObject(const sf::Vector2f& position, const sf::Vector2f& size) : mRect(sf::FloatRect(position.x, position.y, size.x, size.y))
   {}

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

   void StaticObject::setSize(const sf::Vector2f& size)
   {
      mRect.width = size.x;
      mRect.height = size.y;
   }

   void StaticObject::setRect(const sf::FloatRect& rect)
   {
      mRect = rect;
   }
}