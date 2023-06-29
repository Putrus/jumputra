#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game::physics
{
   class StaticObject
   {
   public:
      sf::FloatRect getRect() const;
      sf::Vector2f getPosition() const;
      
      void setPosition(const sf::Vector2f& position);
      void setSize(const sf::Vector2f& size);
      void setRect(const sf::FloatRect& rect);

   private:
      sf::FloatRect mRect;
   };
}