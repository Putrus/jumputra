#include "../inc/Game.h"

namespace jp::game
{
   Game::Game(const Context& context) : mWorld(context)
   {
   }

   void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mWorld, states);
   }

   bool Game::event(const sf::Event& event)
   {
      return mWorld.event(event);
   }
   
   bool Game::update(const sf::Time& dt)
   {
      return mWorld.update(dt);
   }
}