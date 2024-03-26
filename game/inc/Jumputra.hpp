#pragma once

#include "Context.hpp"
#include "StateStack.hpp"

#include "../../logic/inc/Runnable.hpp"

namespace jp::game
{
   class Jumputra : public logic::Runnable
   {
   public:
      Jumputra();

   private:
      void update(float dt) override;

      void draw() override;
      void event() override;

      Context mContext;

      StateStack mStateStack;
   };
}