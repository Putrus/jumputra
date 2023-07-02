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
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         case sf::Keyboard::Left:
         case sf::Keyboard::Right:
         case sf::Keyboard::Space:
            break;
         }
      }
      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {

         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      return true;
   }
}