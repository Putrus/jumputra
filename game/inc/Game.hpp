#pragma once

#include "StateStack.hpp"

#include "../../logic/inc/Engine.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

namespace jp::game
{
   class Game : public logic::Engine
   {
   public:
      Game();

   private:
      void draw() override;
      void event() override;
      void update(float dt) override;

      graphic::Resources mResources;
      graphic::Window mWindow;

      StateStack mStateStack;
   };
}