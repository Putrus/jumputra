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
      struct DynObject
      {
         sf::RectangleShape shape;
         jp::game::physics::DynamicObject dyn;
      } player;

      struct StaObject
      {
         sf::RectangleShape shape;
         jp::game::physics::StaticObject sta;
      };
      std::vector<StaObject> objects;
   };
}