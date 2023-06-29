#pragma once

#include "State.h"

namespace jp::state
{
   class StateGame final : public State
   {
   public:
      StateGame(StateStack* stack, const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

   private:
      sf::CircleShape shape;
      sf::Vector2f speed;
   };
}