#pragma once

#include "../../graphic/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties
   {
      void loadFromFile(const std::string& filename);
      void loadFromJson(const nlohmann::json& json);

      graphic::Properties graphic;
      logic::Properties logic;
   };
}