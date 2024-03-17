#pragma once

#include "../inc/State.hpp"

#include "../../menu/inc/SelectableItem.hpp"

namespace jp::game::states
{
   class StateGame final : public State
   {
   public:
      StateGame(StateStack* stack);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;
   };
}