#include "../inc/Properties.hpp"

namespace jp::algorithm
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      greedy.bots = json.at("greedy").at("bots");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["greedy"]["bots"] = greedy.bots;

      return json;
   }
}  