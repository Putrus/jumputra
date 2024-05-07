#include "../inc/Context.hpp"

namespace jp::game
{
   Context::Context() : language("english", "data/jsons/languages.json")
   {
      resources.loadFromDirectory("data/resources");
      properties.loadFromFile("data/jsons/properties.json");
      language.setLanguage(properties.language);

      window.setSize(sf::Vector2u(properties.graphic.window.size.x, properties.graphic.window.size.y));
      window.setVerticalSyncEnabled(true);
      window.setFramerateLimit(60);
      window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f),
         sf::Vector2f(static_cast<float>(properties.graphic.window.size.x),
         static_cast<float>(properties.graphic.window.size.y)))));
   }
}