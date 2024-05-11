#pragma once

#include "../inc/StateMenu.hpp"

namespace jp::game
{
   class StateLanguage final : public StateMenu
   {
   public:
      StateLanguage(StateStack* stack, Context& context);
      virtual void update(float dt) override;
      
   private:
      void performSelected() override;
      void close() override;
   };
}