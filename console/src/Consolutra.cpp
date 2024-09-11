#include "../inc/Consolutra.hpp"

#include "../../algorithm/inc/AntColony.hpp"
#include "../../algorithm/inc/DecisionTree.hpp"
#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"
#include "../../algorithm/inc/QLearning.hpp"

#include "../../core/inc/String.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::console
{
   Consolutra::Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName)
      : mLogger(), mWorld(core::String::toLower(std::filesystem::path(worldFilename).stem().string()))
   {
      mProperties.loadFromJsonFile(propertiesFilename);
      mLogger = std::make_shared<core::Logger>("data/logs/" + mWorld + "_" +
         core::String::toLower(algorithmName) + "_" + core::String::currentDate() + ".txt", true);
      mEngine = std::make_shared<logic::Engine>(mProperties.logic, worldFilename);
      mAlgorithm = algorithm::Algorithm::create(algorithm::Algorithm::stringToName(algorithmName), mEngine, mLogger, mProperties.algorithm);
   }

   void Consolutra::run()
   {
      while (!mEngine->getWinner())
      {
         mEngine->update(mEngine->getProperties().secondsPerUpdate);
         mAlgorithm->update(mEngine->getProperties().secondsPerUpdate);
      }

      mAlgorithm->saveStatistics("data/statistics/" + core::String::currentDate() + ".json");
   }
}