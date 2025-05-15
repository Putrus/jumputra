#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Eventable
   {
   public:
      virtual void event(const std::optional<sf::Event>& event) = 0;
   };
}