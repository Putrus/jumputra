#pragma once

namespace jp
{
   class Jumputra
   {
   public:
      Jumputra();

      void run();

   private:
      void draw();
      void event();
      void update();

      states::StateStack mStateStack;
   };
}