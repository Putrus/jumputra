#pragma once

#include "../inc/State.hpp"

namespace jp::game::states
{
   class StateMenu final : public State
   {
   public:
      StateMenu(StateStack* stack);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

   private:
      void updateSelected(int direction);
      void performSelected();
   };
}