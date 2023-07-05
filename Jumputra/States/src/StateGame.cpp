#include "../inc/StateGame.h"

#include <json/json.h>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context), mGame(context) {}

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mGame, states);
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
         }
      }
      return mGame.event(event);
   }

   bool StateGame::update(const sf::Time& dt)
   {
      return mGame.update(dt);
   }
}