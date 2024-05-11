#include "../inc/StateGame.hpp"

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context) : State(stack, context), mGame(context) {}

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mGame);
   }

   void StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::Closed)
      {
         mGame.save();
      }

      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Escape:
            mGame.save();
            popState();
            break;
         default:
            break;
         }
      }

      mGame.event(event);
   }

   void StateGame::update(float dt)
   {
      mGame.update(dt);
   }
}