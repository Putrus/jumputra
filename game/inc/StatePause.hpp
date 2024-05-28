#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StatePause final : public StateMenu
   {
   public:
      StatePause(StateStack* stack, Context& context);
      virtual void update(float dt) override;

   private:
      void performSelected() override;
      void close() override;
   };
}