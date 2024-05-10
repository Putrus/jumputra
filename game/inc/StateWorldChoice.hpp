#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateWorldChoice final : public StateMenu
   {
   public:
      StateWorldChoice(StateStack* stack, Context& context);

   protected:
      void performSelected() override;
      void close() override;
   };
}