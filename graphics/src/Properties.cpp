#include "../inc/Properties.hpp"

namespace jp::graphics
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      language = json.at("language");
      window.size.x = json.at("window").at("size").at("x");
      window.size.y = json.at("window").at("size").at("y");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["language"] = language;  
      
      json["window"]["size"]["x"] = window.size.x;
      json["window"]["size"]["y"] = window.size.y;

      return json;
   }
}