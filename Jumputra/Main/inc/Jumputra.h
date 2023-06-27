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

      std::shared_ptr<sf::RenderWindow> mWindow;
      std::shared_ptr<res::FontManager> mFontManager;
      std::shared_ptr<state::StateStack> mStateStack;

      sf::Time mTimePerFrame;
   };
}