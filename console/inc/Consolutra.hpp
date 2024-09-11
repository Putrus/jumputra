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
      Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName);

      void run();
      
   private:
      Properties mProperties;

      std::string mWorld;

      std::shared_ptr<logic::Engine> mEngine;
      std::shared_ptr<core::Logger> mLogger;
      std::unique_ptr<algorithm::Algorithm> mAlgorithm;
   };
}