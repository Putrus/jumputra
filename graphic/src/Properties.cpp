#include "../inc/Properties.hpp"

namespace jp::graphic
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
      json.at("language") = language;  
      
      json.at("window").at("size").at("x") = window.size.x;
      json.at("window").at("size").at("y") = window.size.y;

      return json;
   }
}