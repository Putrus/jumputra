#pragma once

#include <SFML/Graphics.hpp>

#include "../../core/inc/Jsonable.hpp"

namespace jp::graphic
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      std::string language;

      struct Window
      {
         sf::Vector2u size;
      } window;
   };
}