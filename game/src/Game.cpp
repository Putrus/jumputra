#include "../inc/Context.hpp"
#include "../inc/Game.hpp"

namespace jp::game
{
   Game::Game() : mStateStack(states::StateID::Menu)
   {
   }

   void Game::run()
   {
      sf::Clock clock;
      sf::Time time = sf::Time::Zero;
      while (Context::get()->window.isOpen())
      {
         event();
         time += clock.restart();
         while (time >= Context::get()->timePerFrame)
         {
            time -= Context::get()->timePerFrame;
            update();
         }
         draw();
      }
   }

   void Game::draw()
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

   void Game::update()
   {
      mStateStack.update(16.f);
   }
}