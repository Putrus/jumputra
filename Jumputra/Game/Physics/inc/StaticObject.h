#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"

namespace jp::game::physics
{
   class StaticObject
   {
   public:
      StaticObject();
      StaticObject(const sf::FloatRect& rect);
      StaticObject(const sf::Vector2f& position, const sf::Vector2f& size);

      sf::FloatRect getRect() const;
      sf::Vector2f getPosition() const;
      
      void setPosition(const sf::Vector2f& position);
      void setSize(const sf::Vector2f& size);
      void setRect(const sf::FloatRect& rect);

   private:
      sf::FloatRect mRect;
   };
}