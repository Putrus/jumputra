#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

namespace jp::graphic
{
   struct Properties
   {
      void loadFromJson(const nlohmann::json& json);

      struct Window
      {
         sf::Vector2u size;
      } window;
   };
}