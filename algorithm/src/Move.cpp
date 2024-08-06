#include "../inc/Move.hpp"

namespace jp::algorithm
{
   void Move::fromJson(const nlohmann::json& json)
   {
      type = json.at("move");
      direction = static_cast<logic::CharacterDirection>(json.at("direction"));
      value = json.at("value");
   }

   nlohmann::json Move::toJson() const
   {
      nlohmann::json json;
      json["type"] = type;
      json["direction"] = static_cast<int>(direction);
      json["value"] = value;
      return json;
   }
}