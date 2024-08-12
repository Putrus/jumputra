#include "../inc/Consolutra.hpp"

#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::console
{
   Consolutra::Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName)
   {
      mProperties.loadFromJsonFile(propertiesFilename);
      mEngine = std::make_shared<logic::Engine>(mProperties.logic);
      mEngine->loadFromJsonFile(worldFilename);
      if (algorithmName == "genetic")
      {
         mAlgorithm = std::make_unique<algorithm::Genetic>(mEngine, mProperties.algorithm.genetic.population.size);
      }
      else if (algorithmName == "greedy")
      {
         mAlgorithm = std::make_unique<algorithm::Greedy>(mEngine, mProperties.algorithm.greedy.bots);
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

      std::cout << mEngine->getStatistics() << std::endl;
   }
}