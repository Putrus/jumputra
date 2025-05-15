#include "../inc/Jumputra.hpp"

namespace jp::game
{
   Jumputra::Jumputra() : mStateStack(StateID::MainMenu, mContext),
      Runnable(mContext.properties.logic.secondsPerUpdate) {}

   void Jumputra::update(float dt)
   {
      mStateStack.update(dt);

      if (!mContext.window.isOpen())
      {
         terminate();
      }
   }

   void Jumputra::draw()
   {
      mContext.window.clear();
      mContext.window.draw(mStateStack);
      mContext.window.display();
   }

   void Jumputra::event()
   {
      while (const std::optional event = mContext.window.pollEvent())
      {
         mStateStack.event(event.value());

         if (event->is<sf::Event::Closed>())
         {
            mContext.window.close();
         }
         
         if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
         {
            switch (keyPressed->scancode)
            {
            case sf::Keyboard::Scancode::F1:
               mContext.window.setSize(sf::Vector2u(480, 360));
               break;
            case sf::Keyboard::Scancode::F2:
               mContext.window.setSize(sf::Vector2u(720, 540));
               break;
            case sf::Keyboard::Scancode::F3:
               mContext.window.setSize(sf::Vector2u(960, 720));
            default:
               break;
            }
         }
      }
   }
}