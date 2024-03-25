#include "../inc/Window.hpp"

namespace jp::graphic
{
   Window::Window(const sf::Vector2u& size) : sf::RenderWindow(sf::VideoMode(size), "jumputra") {}
}