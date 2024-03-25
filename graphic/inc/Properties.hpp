#pragma once

#include "../../math/inc/Vector2.hpp"


namespace jp::graphic
{
   struct Properties
   {
      struct Window
      {
         math::Vector2<float> size;
      } window;

      bool loadFromFile(const std::string& filename);
      //bool loadFromJson(const nlohmann::json& json);
   };
}