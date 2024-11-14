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
   constexpr int MAX_EXECUTION_MINUTES = 2;
   constexpr int EXECUTION_NUMBER = 24;

   Consolutra::Consolutra(const std::shared_ptr<logic::Engine>& engine, const Properties& properties, const std::string& worldFilename,
      const std::string& resultDirectory, algorithm::AlgorithmName algorithmName, const std::shared_ptr<core::Logger>& logger)
      : mLogsDirectory(resultDirectory), mStatisticsDirectory(resultDirectory), mCurrentDate(core::String::currentDateWithSeconds()), mStartTime(std::chrono::steady_clock::now()),
      mProperties(properties), mWorld(core::String::toLower(std::filesystem::path(worldFilename).stem().string())), mLogger(logger), mEngine(engine)
   {
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

         if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - mStartTime).count() >= MAX_EXECUTION_MINUTES)
         {
            *mLogger << "The algorithm takes more than " << MAX_EXECUTION_MINUTES << " minutes, terminated" << std::endl;
            break;
         }

         if (mEngine->getCharacters().empty())
         {
            *mLogger << "No character exists, terminated" << std::endl;
            break;
         }
      }
      // std::string filename = mStatisticsDirectory +
      //    core::String::toLower(mWorld + "_" + mAlgorithm->getName()) + "_" + mCurrentDate + ".json";
      // mAlgorithm->saveStatistics(filename);
   }

   void Consolutra::investigate()
   {
      std::fstream csvFile;
      algorithm::AlgorithmName algorithmName = algorithm::Algorithm::stringToName(mAlgorithm->getName());
      std::string resultDir = "data/console/" + core::String::toLower(mAlgorithm->getName()) + '_' + mCurrentDate + "/";
      std::filesystem::create_directories(resultDir);
      csvFile.open(resultDir + "result.csv", std::ios::out | std::ios::app);
      if (!csvFile.is_open())
      {
         throw std::runtime_error("jp::console::Consolutra::investigate - Failed to open csv file");
      }

      switch(algorithmName)
      {
         case algorithm::AlgorithmName::Genetic:
         {
            geneticInvestigation(csvFile, resultDir, algorithmName);
         }
         break;
         case algorithm::AlgorithmName::Greedy:
         {
            greedyInvestigation(csvFile, resultDir, algorithmName);
         }
         break;
         case algorithm::AlgorithmName::DecisionTree:
         {
            decisionTreeInvestigation(csvFile, resultDir, algorithmName);
         }
         break;
      }

      csvFile.close();
   }

   void Consolutra::geneticInvestigation(std::fstream& csvFile, const std::string& resultDir, algorithm::AlgorithmName algorithmName)
   {
      csvFile << "id;completed;population size;population elitism;mutation change;mutation max;tournament;visited segments impact;jump moves;moves;falls;jumps;time;totalTime;" << std::endl;
      Properties properties = mProperties;
      int id = 0;
      for (int populationSize = 50; populationSize < 800; populationSize += 50)
      {
         properties.algorithm.genetic.population.size = populationSize;
         for (float populationElitism = 0.125; populationElitism < 0.6; populationElitism += 0.125)
         {
            properties.algorithm.genetic.population.elitism = populationElitism;
            for (float mutationChange = 0.002; mutationChange < 0.02; mutationChange += 0.002)
            {
               properties.algorithm.genetic.mutation.change = mutationChange;
               for (float mutationMax = 0.02; mutationMax < 0.09; mutationMax += 0.02)
               {
                  properties.algorithm.genetic.mutation.change = mutationMax;
                  for (float tournament = 0.1; tournament < 1.0; tournament += 0.1)
                  {
                     properties.algorithm.genetic.tournament = tournament;
                     for (float visitedSegmentsImpact = 1.0; visitedSegmentsImpact < 20; ++visitedSegmentsImpact)
                     {
                        properties.algorithm.genetic.visitedSegmentsImpact = visitedSegmentsImpact;
                        auto engineCopy = std::make_shared<logic::Engine>(*mEngine);
                        engineCopy->removeAllCharacters();
                        engineCopy->addCharacter(mEngine->getCharacters().front()->getRect());
                        Consolutra consolutra(engineCopy, properties, mWorldFilename, resultDir, algorithmName, mLogger);
                        consolutra.run();
                        bool completed = consolutra.mEngine->getWinner() ? true : false;
                        const logic::Statistics& statistics = consolutra.mEngine->getStatistics();
                        auto moves = consolutra.mAlgorithm->getMoves();
                        int jumpMoves = std::count_if(moves.begin(), moves.end(), [](const algorithm::Move &move)
                           { return move.type == algorithm::MoveType::Jump; });
                        csvFile << id << ';' << completed << ';' << populationSize << ';' << populationElitism << ';' <<
                           mutationChange << ';' << mutationMax << ';' << tournament << ';' << visitedSegmentsImpact << ';' <<
                           jumpMoves << ';' << moves.size() << ';' << statistics.falls << ';' << statistics.jumps << ';' <<
                           statistics.time << ';' << statistics.totalTime << ';';
                        ++id;
                     }
                  }
               }
            }
         }
      }
   }

   void Consolutra::greedyInvestigation(std::fstream& csvFile, const std::string& resultDir, algorithm::AlgorithmName algorithmName)
   {
      csvFile << "id;completed;bots;epsilon;moves;falls;jumps;time;totalTime;" << std::endl;
      Properties properties = mProperties;
      int id = 0;
      for (int bots = 10; bots < 200; bots += 10)
      {
         properties.algorithm.greedy.bots = bots;
         for (float epsilon = 0.05f; epsilon < 0.7f; epsilon += 0.05f)
         {
            properties.algorithm.greedy.epsilon = epsilon;
            for (int i = 0; i < EXECUTION_NUMBER; ++i)
            {
               *mLogger << "Run with parameters: " << std::endl;
               *mLogger << "bots = " << bots << std::endl;
               *mLogger << "epsilon = " << epsilon << std::endl;
               auto engineCopy = std::make_shared<logic::Engine>(*mEngine);
               engineCopy->removeAllCharacters();
               engineCopy->addCharacter(mEngine->getCharacters().front()->getRect());
               Consolutra consolutra(engineCopy, properties, mWorldFilename, resultDir, algorithmName, mLogger);
               consolutra.run();
               bool completed = consolutra.mEngine->getWinner() ? true : false;
               logic::Statistics statistics = consolutra.mEngine->getStatistics();
               csvFile << id << ';' << completed << ';' << bots << ';' << epsilon << ';' << consolutra.mAlgorithm->getMoves().size() << ';' <<
                  statistics.falls << ';' << statistics.jumps << ';' << statistics.time << ';' << statistics.totalTime << ';' << std::endl;
               ++id;
            }
         }
      }
   }

   void Consolutra::decisionTreeInvestigation(std::fstream& csvFile, const std::string& resultDir, algorithm::AlgorithmName algorithmName)
   {
      csvFile << "id;completed;decision jumps;jump value;run value;jump moves;moves;falls;jumps;time;totalTime;" << std::endl;
      Properties properties = mProperties;
      int id = 0;
      for (int jumps = 2; jumps <= 100; jumps += 2)
      {
         properties.algorithm.decisionTree.jumps = jumps;
         for (float runValue = 0.025f; runValue <= 1.f; runValue += 0.025f)
         {
            properties.algorithm.decisionTree.runValue = runValue;
            auto engineCopy = std::make_shared<logic::Engine>(*mEngine);
            engineCopy->removeAllCharacters();
            engineCopy->addCharacter(mEngine->getCharacters().front()->getRect());
            Consolutra consolutra(engineCopy, properties, mWorldFilename, resultDir, algorithmName, mLogger);
            consolutra.run();
            bool completed = consolutra.mEngine->getWinner() ? true : false;
            const logic::Statistics& statistics = consolutra.mEngine->getStatistics();
            auto moves = consolutra.mAlgorithm->getMoves();
            int jumpMoves = std::count_if(moves.begin(), moves.end(), [](const algorithm::Move &move)
               { return move.type == algorithm::MoveType::Jump; });
            csvFile << id << ';' << completed << ';' << jumps << ';' << properties.algorithm.decisionTree.jumpValue << ';' << runValue << ';' <<
               jumpMoves << ';' << moves.size() << ';' << statistics.falls << ';' << statistics.jumps << ';' <<
               statistics.time << ';' << statistics.totalTime << ';' << std::endl;
            ++id;
         }  
      }
   }
}