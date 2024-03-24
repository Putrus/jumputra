#pragma once

#include "../resources/inc/Resources.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Context
   {
   public:
      Context(Context&) = delete;
      void operator=(const Context&) = delete;

      static Context* get();

      sf::RenderWindow window;
      res::Resources resources;

   protected:
      Context(const sf::VideoMode videoMode, const std::string& windowName);

      static Context* context;
   };
}