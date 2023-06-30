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
         bool duringSpace = false;
         bool jumping = false;
         float jumpSpeed = 0.f;

         void setPosition(const sf::Vector2f& position)
         {
            shape.setPosition(position);
            dyn.setPosition(position);
         }

         void setSize(const sf::Vector2f& size)
         {
            shape.setSize(size);
            dyn.setSize(size);
         }
      } player;

      struct StaObject
      {
         sf::RectangleShape shape;
         jp::game::physics::StaticObject sta;

         void setPosition(const sf::Vector2f& position)
         {
            shape.setPosition(position);
            sta.setPosition(position);
         }

         void setSize(const sf::Vector2f& size)
         {
            shape.setSize(size);
            sta.setSize(size);
         }
      };
      std::vector<StaObject> objects;
   };
}