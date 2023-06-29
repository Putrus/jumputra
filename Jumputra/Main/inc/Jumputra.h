#pragma once

#include "../../States/inc/StateStack.h"

namespace jp
{
   class Jumputra final
   {
   public:
      Jumputra(unsigned int sizeX, unsigned int sizeY);

      void run();

   private:
      void processEvents();
      void render();
      void update(sf::Time& dt);

      sf::RenderWindow mWindow;
      sf::Time mTimePerFrame;
      
      res::Resources mResources;

      state::StateStack mStateStack;
   };
}