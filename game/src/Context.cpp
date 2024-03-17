#include "../inc/Context.hpp"

namespace jp::game
{
   Context* Context::context = nullptr;
   
   Context::Context(const sf::VideoMode videoMode, const std::string& windowName)
      : window(videoMode, windowName)
   {
      window.setFramerateLimit(0);
      window.setVerticalSyncEnabled(true);
   }

   Context* Context::get()
   {
      if (context == nullptr)
      {
         context = new Context(sf::VideoMode(sf::Vector2u(640, 480)), "jumputra");
      }
      return context;
   }
}