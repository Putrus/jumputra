#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::game
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      language = json["language"];
      
      graphic.window.size.x = json["graphic"]["window"]["size"]["x"];
      graphic.window.size.y = json["graphic"]["window"]["size"]["y"];
      logic.fromJson(json["logic"]);
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["language"] = language;
      
      json["graphic"]["window"]["size"]["x"] = graphic.window.size.x;
      json["graphic"]["window"]["size"]["y"] = graphic.window.size.y;

      json["logic"] = logic.toJson();

      return json;
   }
}