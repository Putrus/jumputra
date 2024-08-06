#include "../inc/Context.hpp"

#include <filesystem>

namespace jp::game
{
   Context::Context()
   {
      resources.loadFromDirectory(RESOURCES_DIR);
      properties.loadFromJsonFile(std::string(OPTIONS_DIR) + "properties.json");
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
      this->language.loadFromJsonFile(std::string(OPTIONS_DIR) + "languages.json");
   }

   void Context::loadWorlds()
   {
      worlds.clear();
      for (const auto& entry : std::filesystem::directory_iterator(WORLDS_DIR))
      {
         if (entry.is_regular_file())
         {
            std::string worldName = entry.path().filename().string();
            std::size_t dotIndex = worldName.find_last_of(".");
            if (dotIndex != std::string::npos)
            {
               worldName = worldName.substr(0, dotIndex);
               worlds.push_back(worldName);
            }
         }
      }
   }
}