#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Eventable
   {
   public:
      virtual void event(const sf::Event& event) = 0;
   };
}