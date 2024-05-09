#pragma once

#include <SFML/Graphics.hpp>

#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties : public logic::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      std::string language;

      struct Graphic
      {
         struct Window
         {
            sf::Vector2u size;
         } window;
      } graphic;

      logic::Properties logic;
   };
}