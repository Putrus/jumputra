#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateMainMenu final : public StateMenu
   {
   public:
      StateMainMenu(StateStack* stack, Context& context);
      virtual void update(float dt) override;

   private:
      void performSelected();
      void close();
   };
}