#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::game
{
   void Properties::loadFromJson(const nlohmann::json& json)
   {
      language = json["language"];
      
      graphic.loadFromJson(json);
      logic.loadFromJson(json);
   }
}