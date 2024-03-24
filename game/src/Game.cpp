#include "../inc/Context.hpp"
#include "../inc/Game.hpp"

namespace jp::game
{
   Game::Game() : mStateStack(states::StateID::Menu), logic::Logic(mProperties)
   {
      //TODO
      mProperties.logic.secondsPerFrame = 1.f / 60.f;
   }

   void Game::draw() const
   {
      Context::get()->window.clear();
      Context::get()->window.draw(mStateStack);
      Context::get()->window.display();
   }

   void Game::event()
   {
      sf::Event event;
      while (Context::get()->window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            Context::get()->window.close();
         }

         mStateStack.event(event);
      }
   }

   void Game::update(float dt)
   {
      mStateStack.update(dt);
   }
}