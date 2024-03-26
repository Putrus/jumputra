#pragma once

#include "../inc/Menu.hpp"
#include "../inc/State.hpp"

namespace jp::game
{
   class StateMenu final : public State
   {
   public:
      StateMenu(StateStack* stack);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

   private:
      void performSelected();

      Menu mMenu;
   };
}