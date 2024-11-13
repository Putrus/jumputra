#include "../inc/Properties.hpp"

namespace jp::algorithm
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      antColony.ants = json.at("antColony").at("ants");
      antColony.randomJumpChance = json.at("antColony").at("randomJumpChance");
      antColony.evaporationRate = json.at("antColony").at("evaporationRate");
      antColony.maxIntensity = json.at("antColony").at("maxIntensity");
      antColony.minIntensity = json.at("antColony").at("minIntensity");

      decisionTree.jumps = json.at("decisionTree").at("jumps");
      decisionTree.jumpValue = json.at("decisionTree").at("jumpValue");
      decisionTree.runValue = json.at("decisionTree").at("runValue");

      genetic.population.size = json.at("genetic").at("population").at("size");
      genetic.population.elitism = json.at("genetic").at("population").at("elitism");
      genetic.mutation.change = json.at("genetic").at("mutation").at("change");
      genetic.mutation.max = json.at("genetic").at("mutation").at("max");
      genetic.tournament = json.at("genetic").at("tournament");
      genetic.visitedSegmentsImpact = json.at("genetic").at("visitedSegmentsImpact");

      greedy.bots = json.at("greedy").at("bots");
      greedy.epsilon = json.at("greedy").at("epsilon");

      qLearning.learningRate = json.at("qLearning").at("learningRate");
      qLearning.discountFactor = json.at("qLearning").at("discountFactor");
      qLearning.epsilon = json.at("qLearning").at("epsilon");
      qLearning.randomJumpChance = json.at("qLearning").at("randomJumpChance");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["antColony"]["ants"] = antColony.ants;
      json["antColony"]["randomJumpChance"] = antColony.randomJumpChance;
      json["antColony"]["evaporationRate"] = antColony.evaporationRate;
      json["antColony"]["maxIntensity"] = antColony.maxIntensity;
      json["antColony"]["minIntensity"] = antColony.minIntensity;

      json["decisionTree"]["jumps"] = decisionTree.jumps;
      json["decisionTree"]["jumpValue"] = decisionTree.jumpValue;
      json["decisionTree"]["runValue"] = decisionTree.runValue;
      
      json["genetic"]["population"]["size"] = genetic.population.size;
      json["genetic"]["population"]["elitism"] = genetic.population.elitism;
      json["genetic"]["mutation"]["change"] = genetic.mutation.change;
      json["genetic"]["mutation"]["max"] = genetic.mutation.max;
      json["genetic"]["tournament"] = genetic.tournament;
      json["genetic"]["visitedSegmentsImpact"] = genetic.visitedSegmentsImpact;

      json["greedy"]["bots"] = greedy.bots;
      json["greedy"]["epsilon"] = greedy.epsilon;

      json["qLearning"]["learningRate"] = qLearning.learningRate;
      json["qLearning"]["discountFactor"] = qLearning.discountFactor;
      json["qLearning"]["epsilon"] = qLearning.epsilon;
      json["qLearning"]["randomJumpChance"] = qLearning.randomJumpChance;

      return json;
   }
}  