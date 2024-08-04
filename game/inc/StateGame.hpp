#pragma once

#include "../inc/Game.hpp"
#include "../inc/State.hpp"

#include "../../agents/inc/Agent.hpp"

namespace jp::game
{
   class StateGame final : public State
   {
   public:
      StateGame(StateStack* stack, Context& context);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

   private:
      std::shared_ptr<Game> mGame;
      std::unique_ptr<agents::Agent> mAgent;
   };
}