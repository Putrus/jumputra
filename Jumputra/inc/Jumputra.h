#pragma once

#include <SFML/Graphics.hpp>

namespace put
{
   class Jumputra
   {
   public:
      Jumputra(unsigned int sizeX, unsigned int sizeY);

      void run();

   private:
      std::unique_ptr<sf::RenderWindow> window;
   };
}