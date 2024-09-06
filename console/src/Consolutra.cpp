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
      : mLogger(std::make_shared<core::Logger>("data/logs/" + core::String::toLower(std::filesystem::path(worldFilename).filename().string()) + "_" +
         core::String::toLower(algorithmName) + "_" + core::String::currentDate() + ".txt", true))
   {
      mProperties.loadFromJsonFile(propertiesFilename);
      mEngine = std::make_shared<logic::Engine>(mProperties.logic);
      mEngine->loadFromJsonFile(worldFilename);
      if (algorithmName == "antColony")
      {
         mAlgorithm = std::make_unique<algorithm::AntColony>(mEngine, mLogger, mProperties.algorithm);
      }
      else if (algorithmName == "decisionTree")
      {
         mAlgorithm = std::make_unique<algorithm::DecisionTree>(mEngine, mLogger, mProperties.algorithm);
      }
      else if (algorithmName == "genetic")
      {
         mAlgorithm = std::make_unique<algorithm::Genetic>(mEngine, mLogger, mProperties.algorithm);
      }
      else if (algorithmName == "greedy")
      {
         mAlgorithm = std::make_unique<algorithm::Greedy>(mEngine, mLogger, mProperties.algorithm);
      }
      else if (algorithmName == "qLearning")
      {
         mAlgorithm = std::make_unique<algorithm::QLearning>(mEngine, mLogger, mProperties.algorithm);
      }
      else
      {
         throw std::invalid_argument("Consolutra::Consolutra - Failed to create algorithm, wrong name");
      }
   }

   void Consolutra::run()
   {
      while (!mEngine->hasGoalBeenAchieved())
      {
         mEngine->update(1 / 60.f);
         mAlgorithm->update(1 / 60.f);
      }

      *mLogger << "Moves:" << mAlgorithm->getMoves().size() << std::endl;
      for (size_t i = 0; i < mAlgorithm->getMoves().size();  ++i)
      {
         *mLogger << i << " " << mAlgorithm->getMoves().at(i) << std::endl;
      }

      *mLogger << "Statistics: " << mEngine->getStatistics() << std::endl;
   }
}