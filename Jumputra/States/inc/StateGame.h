#pragma once

#include "State.h"
#include "../../Game/Physics/inc/DynamicObject.h"

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
      void StateGame::loadLastJson();

      std::vector<game::physics::StaticObject> mObjects;
      game::physics::DynamicObject mPlayer;
   };
}