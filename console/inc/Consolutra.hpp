#pragma once

#include "Properties.hpp"

#include "../../algorithm/inc/Algorithm.hpp"
#include "../../core/inc/Logger.hpp"
#include "../../logic/inc/Engine.hpp"

namespace jp::console
{
   class Consolutra
   {
   public:
      Consolutra(const std::shared_ptr<logic::Engine>& engine, const Properties& properties, const std::string& worldFilename,
         const std::string& resultDirectory, algorithm::AlgorithmName algorithmName);
      Consolutra(const Properties& properties, const std::string& worldFilename,
         const std::string& resultDirectory, algorithm::AlgorithmName algorithmName);
      Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName);

      void run();
      void investigate();

      void greedyInvestigation(std::fstream& csvFile, const std::string& resultDir, algorithm::AlgorithmName algorithmName);
      void decisionTreeInvestigation(std::fstream& csvFile, const std::string& resultDir, algorithm::AlgorithmName algorithmName);

   private:
      Properties mProperties;

      std::string mWorld;
      std::string mWorldFilename;
      std::string mCurrentDate;
      std::string mLogsDirectory;
      std::string mStatisticsDirectory;

      std::shared_ptr<logic::Engine> mEngine;
      std::shared_ptr<core::Logger> mLogger;
      std::unique_ptr<algorithm::Algorithm> mAlgorithm;

      std::chrono::steady_clock::time_point mStartTime;
   };
}