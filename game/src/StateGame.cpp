#include "../inc/StateGame.hpp"

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context) : State(stack, context), mGame(context.properties.logic) {}

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mGame);
   }

   void StateGame::event(const sf::Event& event) {}

   void StateGame::update(float dt)
   {
      mGame.update(dt);
   }
}