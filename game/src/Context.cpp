#include "../inc/Context.hpp"

namespace jp::game
{
   Context::Context()
   {
      resources.loadFromDirectory("data/resources");
      properties.loadFromJsonFile("data/jsons/properties.json");
      setLanguage(properties.graphic.language);

      window.setSize(sf::Vector2u(properties.graphic.window.size.x, properties.graphic.window.size.y));
      window.setVerticalSyncEnabled(true);
      window.setFramerateLimit(60);
      window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f),
         sf::Vector2f(static_cast<float>(properties.graphic.window.size.x),
         static_cast<float>(properties.graphic.window.size.y)))));
   }

   void Context::setLanguage(const std::string& language)
   {
      properties.graphic.language = language;
      this->language.setLanguage(language);
      this->language.loadFromJsonFile("data/jsons/languages.json");
   }
}