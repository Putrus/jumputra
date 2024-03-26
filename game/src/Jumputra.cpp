#include "../inc/Jumputra.hpp"

namespace jp::game
{
   Jumputra::Jumputra() : mStateStack(StateID::Menu, mContext),
      Runnable(mContext.properties.logic.secondsPerUpdate) {}

   void Jumputra::update(float dt)
   {
      mStateStack.update(dt);
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
         if (event.type == sf::Event::Closed)
         {
            mContext.window.close();
         }

         mStateStack.event(event);
      }
   }
}