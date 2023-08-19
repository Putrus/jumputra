#include "../inc/Game.h"

namespace jp::game
{
   Game::Game(const Context& context) : mWorld(context),
      mView(sf::FloatRect(0.f, 15120.f, static_cast<float>(context.window.getSize().x),
      static_cast<float>(context.window.getSize().y))), mContext(context)
   {
      context.window.setView(mView);
   }

   void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mWorld, states);
   }

   bool Game::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Up:
            mView.move(sf::Vector2f(0.f, -360));
            mContext.window.setView(mView);
            break;
         case sf::Keyboard::Down:
            mView.move(sf::Vector2f(0.f, 360));
            mContext.window.setView(mView);
            break;
         }
      }
      return mWorld.event(event);
   }
   
   bool Game::update(const sf::Time& dt)
   {
      return mWorld.update(dt);
   }
}