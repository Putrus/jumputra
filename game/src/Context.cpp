#include "../inc/Context.hpp"

namespace jp::game
{
   Context::Context()
   {
      resources.loadFromDirectory("data/resources");
      properties.loadFromFile("data/jsons/properties.json");
      window.setSize(sf::Vector2u(properties.graphic.window.size.x, properties.graphic.window.size.y));
      window.setVerticalSyncEnabled(true);
      window.setFramerateLimit(60);
   }
}