#include "../inc/Context.hpp"

namespace jp::game
{
   Context::Context()
   {
      if (!resources.loadFromDirectory("data/resources"))
      {
         throw std::invalid_argument("Context::Context - Failed to load resources");
      }

      if (!properties.loadFromFile("data/jsons/properties.json"))
      {
         throw std::invalid_argument("Context::Context - Failed to load properties");
      }

      window.setSize(sf::Vector2u(properties.graphic.window.size.x, properties.graphic.window.size.y));
   }
}