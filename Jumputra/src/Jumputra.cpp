#include "../inc/Jumputra.h"

#include <iostream>

namespace jumputra
{
   Jumputra::Jumputra(unsigned int sizeX, unsigned int sizeY) : window(new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), "Jumputra")),
      fontManager(new FontManager())
   {
      fontManager->load(Font::Pixel, "Resources/Fonts/Pixel.ttf");
   }

   void Jumputra::run()
   {
      sf::Clock clock;
      sf::Time timeSinceLastUpdate = sf::Time::Zero;
      while (window->isOpen())
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
      while (window->pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window->close();

         if (event.type == sf::Event::KeyReleased)
         {
            if (event.key.code == sf::Keyboard::F11)
            {
               std::cout << window->getSize().x << " " << window->getSize().y << std::endl;
            }
         }
      }
   }

   void Jumputra::render()
   {
      window->clear();
      //window->draw();
      window->display();
   }

   void Jumputra::update(const sf::Time& elapsedTime)
   {

   }

}