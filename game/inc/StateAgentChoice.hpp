#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateAgentChoice final : public StateMenu
   {
   public:
      StateAgentChoice(StateStack* stack, Context& context);
      virtual void update(float dt) override;

   protected:
      void performSelected() override;
      void close() override;
   };
}