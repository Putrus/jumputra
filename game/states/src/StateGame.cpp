#include "../inc/StateGame.hpp"

#include "../../inc/Context.hpp"

namespace jp::game::states
{
   StateGame::StateGame(StateStack* stack) : State(stack) {}

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {}

   void StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Escape:
            popState();
            break;
         }
      }
   }

   void StateGame::update(float dt) {}
}