#include "../inc/Game.hpp"

namespace jp::game
{
   Game::Game() : mStateStack(StateID::Menu), logic::Engine() {}

   void Game::draw()
   {
      mWindow.clear();
      mWindow.draw(mStateStack);
      mWindow.display();
   }

   void Game::event()
   {
      sf::Event event;
      while (mWindow.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            mWindow.close();
         }

         mStateStack.event(event);
      }
   }

   void Game::update(float dt)
   {
      mStateStack.update(dt);
   }
}