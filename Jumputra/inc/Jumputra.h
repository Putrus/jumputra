#pragma once

#include "../inc/Menu.h"
#include "../inc/ResourceManager.h"

namespace jumputra
{
   enum JumputraState
   {
      MENU = 0,
      GAME
   };

   class Jumputra
   {
   public:
      Jumputra(unsigned int sizeX, unsigned int sizeY);

      void run();

   private:
      void processEvents();
      void render();
      void update(const sf::Time& elapsedTime);

      std::unique_ptr<sf::RenderWindow> window;
      std::shared_ptr<FontManager> fontManager;
   };
}