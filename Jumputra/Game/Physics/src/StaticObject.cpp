#include "../inc/StaticObject.h"

#include <iostream>

namespace jp::game::physics
{
   StaticObject::StaticObject() {}

   StaticObject::StaticObject(const sf::FloatRect& rect) : mRect(rect) {}

   StaticObject::StaticObject(const sf::Vector2f& position, const sf::Vector2f& size)
      : mRect(sf::FloatRect(position.x, position.y, size.x, size.y)) {}

   void StaticObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      draw(target, states, sf::Color::White);
   }

   sf::FloatRect StaticObject::getRect() const
   {
      return mRect;
   }

   sf::Vector2f StaticObject::getPosition() const
   {
      return mRect.getPosition();
   }

   sf::Vector2f StaticObject::getSize() const
   {
      return mRect.getSize();
   }

   float StaticObject::getLeft() const
   {
      return mRect.left;
   }

   float StaticObject::getTop() const
   {
      return mRect.top;
   }

   float StaticObject::getWidth() const
   {
      return mRect.width;
   }

   float StaticObject::getHeight() const
   {
      return mRect.height;
   }

   float StaticObject::getRight() const
   {
      return mRect.left + mRect.width;
   }

   float StaticObject::getBottom() const
   {
      return mRect.top + mRect.height;
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

   void StaticObject::draw(sf::RenderTarget& target, sf::RenderStates states, const sf::Color& color) const
   {
      sf::VertexArray rectangle(sf::Quads, 4);
      rectangle[0] = sf::Vertex({ getLeft(), getTop() }, color);
      rectangle[1] = sf::Vertex({ getRight(), getTop() }, color);
      rectangle[2] = sf::Vertex({ getRight(), getBottom() }, color);
      rectangle[3] = sf::Vertex({ getLeft(), getBottom() }, color);
      target.draw(rectangle, states);
   }
}