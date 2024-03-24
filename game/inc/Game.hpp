#pragma once

#include "../json/inc/PropertiesLoader.hpp"
#include "../logic/inc/Logic.hpp"
#include "../states/inc/StateStack.hpp"

namespace jp::game
{
   class Game : public logic::Logic
   {
   public:
      Game();

   private:
      void draw() const override;
      void event() override;
      void update(float dt) override;
      
      Properties mProperties;
      json::PropertiesLoader mPropertiesLoader;

      states::StateStack mStateStack;
   };
}