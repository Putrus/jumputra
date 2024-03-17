#pragma once

#include "../resources/inc/Resources.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   struct Context
   {
      sf::RenderWindow window;
      res::Resources resources;
      
   };
}