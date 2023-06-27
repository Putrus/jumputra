#pragma once

#include <SFML/System/Time.hpp>

namespace jp
{
   class Updatable
   {
   public:
      virtual bool update(const sf::Time& dt) = 0;
   };
}