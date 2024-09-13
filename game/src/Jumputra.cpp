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
      sf::Event event;
      while (mContext.window.pollEvent(event))
      {
         mStateStack.event(event);

         if (event.type == sf::Event::Closed)
         {
            mContext.window.close();
         }

         switch (event.key.code)
         {
         case sf::Keyboard::Key::F1:
            mContext.window.setSize(sf::Vector2u(480, 360));
            break;
         case sf::Keyboard::Key::F2:
            mContext.window.setSize(sf::Vector2u(720, 540));
            break;
         case sf::Keyboard::Key::F3:
            mContext.window.setSize(sf::Vector2u(960, 720));
         default:
            break;
         }
      }
   }
}