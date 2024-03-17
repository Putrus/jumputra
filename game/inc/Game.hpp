#pragma once

#include "../states/inc/StateStack.hpp"

namespace jp::game
{
   class Game
   {
   public:
      Game();

      void run();

   private:
      void draw();
      void event();
      void update();
      
      states::StateStack mStateStack;
   };
}