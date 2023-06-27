#pragma once

#include <SFML/Window/Event.hpp>

namespace jp
{
   class Eventable
   {
   public:
      virtual bool event(const sf::Event& event) = 0;
   };
}