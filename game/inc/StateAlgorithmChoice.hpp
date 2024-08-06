#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateAlgorithmChoice final : public StateMenu
   {
   public:
      StateAlgorithmChoice(StateStack* stack, Context& context);
      virtual void update(float dt) override;

   protected:
      void performSelected() override;
      void close() override;
   };
}