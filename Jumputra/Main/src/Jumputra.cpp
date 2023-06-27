#include "../inc/Jumputra.h"

#include <iostream>
#include <memory>

namespace jp
{
   Jumputra::Jumputra(unsigned int sizeX, unsigned int sizeY) :
      mWindow(new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), "Jumputra")),
      mFontManager(new res::FontManager()), mTimePerFrame(sf::seconds(1.f / 60.f))
   {
      mFontManager->load(res::Font::Pixel, "Resources/Fonts/Pixel.ttf");
      state::Context context = { mWindow, mFontManager };
      mStateStack = std::make_shared<state::StateStack>(context);
      mStateStack->pushState(state::StateID::Menu);
   }

   void Jumputra::run()
   {
      sf::Clock clock;
      sf::Time timeSinceLastUpdate = sf::Time::Zero;
      while (mWindow->isOpen())
      {
         processEvents();
         timeSinceLastUpdate += clock.restart();
         update(timeSinceLastUpdate);
         render();
      }
   }

   void Jumputra::processEvents()
   {
      sf::Event event;
      while (mWindow->pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            mWindow->close();
         }

         mStateStack->event(event);
      }
   }

   void Jumputra::render()
   {
      mWindow->clear();
      mWindow->draw(*mStateStack);
      mWindow->display();
   }

   void Jumputra::update(sf::Time& dt)
   {
      while (dt > mTimePerFrame)
      {
         dt -= mTimePerFrame;
         mStateStack->update(mTimePerFrame);
      }
   }
}