#include "../inc/StateGame.h"

#include <iostream>

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
   }

   bool StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         float height = static_cast<float>(mContext.window.getSize().y);
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         }
      }

      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
            //to do
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      return true;
   }
}