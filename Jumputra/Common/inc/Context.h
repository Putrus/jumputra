#pragma once

#include "Resources.h"

namespace jp
{
   struct Context
   {
      Context(sf::RenderWindow& window,
         res::Resources& resources) :
         window(window),
         resources(resources) {}

      sf::RenderWindow& window;
      res::Resources& resources;
   };
}