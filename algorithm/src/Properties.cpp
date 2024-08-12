#include "../inc/Properties.hpp"

namespace jp::algorithm
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      genetic.population.size = json.at("genetic").at("population").at("size");
      genetic.mutation.change = json.at("genetic").at("mutation").at("change");
      genetic.mutation.max = json.at("genetic").at("mutation").at("max");

      greedy.bots = json.at("greedy").at("bots");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["genetic"]["population"]["size"] = genetic.population.size;
      json["genetic"]["mutation"]["change"] = genetic.mutation.change;
      json["genetic"]["mutation"]["max"] = genetic.mutation.max;

      json["greedy"]["bots"] = greedy.bots;

      return json;
   }
}  