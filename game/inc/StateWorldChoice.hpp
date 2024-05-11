#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateWorldChoice final : public StateMenu
   {
   public:
      StateWorldChoice(StateStack* stack, Context& context);
      virtual void update(float dt) override;
      
   protected:
      void performSelected() override;
      void close() override;
   };
}