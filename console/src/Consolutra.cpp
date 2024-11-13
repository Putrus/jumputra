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
   const char* LOGS_DIRECTORY = "data/logs/";
   const char* STATISTICS_DIRECTORY = "data/statistics/";
   constexpr int MAX_EXECUTION_MINUTES = 4;

   Consolutra::Consolutra(const Properties& properties, const std::string& worldFilename,
         const std::string& resultDirectory, algorithm::AlgorithmName algorithmName)
      : mLogsDirectory(resultDirectory), mStatisticsDirectory(resultDirectory), mCurrentDate(core::String::currentDate()), mStartTime(std::chrono::steady_clock::now()), mLogger(),
      mProperties(properties), mWorld(core::String::toLower(std::filesystem::path(worldFilename).stem().string()))
   {
      mLogger = std::make_shared<core::Logger>(resultDirectory + mWorld + "_" +
         core::String::toLower(algorithm::Algorithm::nameToString(algorithmName)) + "_" + core::String::currentDate() + "_log.txt", true);
      mEngine = std::make_shared<logic::Engine>(mProperties.logic, worldFilename);
      mAlgorithm = algorithm::Algorithm::create(algorithmName, mEngine, mLogger, mProperties.algorithm);
   }

   Consolutra::Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName)
      : mLogsDirectory(LOGS_DIRECTORY), mStatisticsDirectory(STATISTICS_DIRECTORY), mCurrentDate(core::String::currentDate()),
      mStartTime(std::chrono::steady_clock::now()), mLogger(), mWorldFilename(worldFilename),
      mWorld(core::String::toLower(std::filesystem::path(worldFilename).stem().string()))
   {
      mProperties.loadFromJsonFile(propertiesFilename);
      mLogger = std::make_shared<core::Logger>(LOGS_DIRECTORY + mWorld + "_" +
         core::String::toLower(algorithmName) + "_" + mCurrentDate + ".txt", true);
      mEngine = std::make_shared<logic::Engine>(mProperties.logic, worldFilename);
      mAlgorithm = algorithm::Algorithm::create(algorithm::Algorithm::stringToName(algorithmName), mEngine, mLogger, mProperties.algorithm);
   }

   void Consolutra::run()
   {
      while (!mEngine->getWinner())
      {
         mEngine->update(mEngine->getProperties().secondsPerUpdate);
         mAlgorithm->update(mEngine->getProperties().secondsPerUpdate);

         if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - mStartTime).count() > MAX_EXECUTION_MINUTES)
         {
            *mLogger << "The algorithm takes more than " << MAX_EXECUTION_MINUTES << " minutes, terminated" << std::endl;
            break;
         }
      }
      std::string filename = mStatisticsDirectory +
         core::String::toLower(mWorld + "_" + mAlgorithm->getName()) + "_" + mCurrentDate + ".json";
      mAlgorithm->saveStatistics(filename);
   }

   void Consolutra::investigate()
   {
      algorithm::AlgorithmName algorithmName = algorithm::Algorithm::stringToName(mAlgorithm->getName());
      std::cout << algorithmName << std::endl;
      switch(algorithmName)
      {
         case algorithm::AlgorithmName::Greedy:
            {
               Properties properties = mProperties;
               for (int bots = 10; bots < 200; bots += 10)
               {
                  properties.algorithm.greedy.bots = bots;
                  for (float epsilon = 0.1f; epsilon < 0.9f; epsilon += 0.1f)
                  {
                     properties.algorithm.greedy.epsilon = epsilon;
                     std::string resultDir = "data/console/" + mCurrentDate + "/" +
                        core::String::toLower(mAlgorithm->getName()) +
                        "/epsilon_" + std::to_string(epsilon) + "_bots_" + std::to_string(bots) + "/";
                     for (int i = 0; i < 100; ++i)
                     {
                        Consolutra consolutra(properties, mWorldFilename, resultDir, algorithmName);
                        consolutra.run();
                     }
                  }
               }
            }
            break;
      }
   }
}