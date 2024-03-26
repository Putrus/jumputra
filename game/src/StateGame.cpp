#include "../inc/StateGame.hpp"

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context) : State(stack, context) {}

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {}

   void StateGame::event(const sf::Event& event) {}

   void StateGame::update(float dt) {}
}