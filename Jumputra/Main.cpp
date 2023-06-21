#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
   sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
   sf::CircleShape shape(100.f);
   shape.setFillColor(sf::Color::Green);
   bool fullscreen = false;

   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();

         if (event.type == sf::Event::KeyReleased)
         {
            if (event.key.code == sf::Keyboard::F11)
            {
               if (fullscreen)
               {
                  fullscreen = false;
                  window.create(sf::VideoMode(200, 200), "SFML works!");
               }
               else
               {
                  fullscreen = true;
                  //window.create(sf::VideoMode(400, 400), "SFML works!");
                  window.create(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
               }
               std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
            }
         }
      }

      window.clear();
      window.draw(shape);
      window.display();
   }

   return 0;
}