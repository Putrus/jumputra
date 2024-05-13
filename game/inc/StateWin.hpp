#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateWin final : public StateMenu
   {
   public:
      StateWin(StateStack* stack, Context& context);

      void update(float dt) override;

   private:
      void performSelected() override;
      void close() override;
   };
}