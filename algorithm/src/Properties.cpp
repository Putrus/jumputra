#include "../inc/Properties.hpp"

namespace jp::algorithm
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      genetic.population.size = json.at("genetic").at("population").at("size");
      genetic.population.elitism = json.at("genetic").at("population").at("elitism");
      genetic.mutation.change = json.at("genetic").at("mutation").at("change");
      genetic.mutation.max = json.at("genetic").at("mutation").at("max");
      genetic.tournament.size = json.at("genetic").at("tournament").at("size");

      greedy.bots = json.at("greedy").at("bots");
      greedy.epsilon = json.at("greedy").at("epsilon");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["genetic"]["population"]["size"] = genetic.population.size;
      json["genetic"]["population"]["elitism"] = genetic.population.elitism;
      json["genetic"]["mutation"]["change"] = genetic.mutation.change;
      json["genetic"]["mutation"]["max"] = genetic.mutation.max;
      json["genetic"]["tournament"]["size"] = genetic.tournament.size;

      json["greedy"]["bots"] = greedy.bots;
      json["greedy"]["epsilon"] = greedy.epsilon;

      return json;
   }
}  