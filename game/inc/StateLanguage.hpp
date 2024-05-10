#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateLanguage final : public StateMenu
   {
   public:
      StateLanguage(StateStack* stack, Context& context);

   private:
      void performSelected();
      void close();
   };
}