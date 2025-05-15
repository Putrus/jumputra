#include "../inc/Context.hpp"

#include <filesystem>

namespace jp::game
{
   Context::Context()
   {
      resources.loadFromDirectory(RESOURCES_DIR);
      properties.loadFromJsonFile(std::string(OPTIONS_DIR) + "properties.json");
      setLanguage(properties.graphic.language);

      sf::Image image(sf::Vector2u(24, 24), sf::Color::Red);
      window.setIcon(image);
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

      std::string directory = newGame ? WORLDS_DIR : SAVES_DIR;
      for (const auto& entry : std::filesystem::directory_iterator(directory))
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