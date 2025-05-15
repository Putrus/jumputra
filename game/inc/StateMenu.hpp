#pragma once

#include "../inc/Menu.hpp"
#include "../inc/State.hpp"

namespace jp::game
{
   class StateMenu : public State
   {
   public:
      StateMenu(StateStack* stack, Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      void event(const std::optional<sf::Event>& event) override;

   protected:
      Menu mMenu;

   private:
      virtual void performSelected() = 0;
      virtual void close() = 0;
      
   };
}