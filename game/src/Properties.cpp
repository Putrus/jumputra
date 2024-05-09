#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::game
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      graphic.fromJson(json.at("graphic"));
      logic.fromJson(json.at("logic"));
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json.at("graphic") = graphic.toJson();
      json.at("logic") = logic.toJson();
      return json;
   }
}