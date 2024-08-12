#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::console
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      algorithm.fromJson(json.at("algorithm"));
      logic.fromJson(json.at("logic"));
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["algorithm"] = algorithm.toJson();
      json["logic"] = logic.toJson();
      return json;
   }
}