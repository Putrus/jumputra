#pragma once

#include "StateStack.hpp"

#include "../../logic/inc/Engine.hpp"

#include "../../graphic/inc/Resources.hpp"

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

      sf::RenderWindow mWindow;
      graphic::Resources mResources;

      StateStack mStateStack;
   };
}