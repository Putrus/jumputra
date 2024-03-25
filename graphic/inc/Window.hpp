#pragma once

#include <SFML/Graphics.hpp>

namespace jp::graphic
{
   class Window : public sf::RenderWindow
   {
   public:
      Window(const sf::Vector2u& size);
   };
}