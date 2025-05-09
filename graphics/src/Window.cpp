#include "../inc/Window.hpp"

namespace jp::graphics
{
   Window::Window() : sf::RenderWindow(sf::VideoMode(sf::Vector2u(640, 480)), "jumputra") {}

   Window::Window(const sf::Vector2u& size) : sf::RenderWindow(sf::VideoMode(size), "jumputra") {}
}