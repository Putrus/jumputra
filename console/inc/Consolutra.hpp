#pragma once

#include "../../algorithm/inc/Algorithm.hpp"
#include "../../algorithm/inc/Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <string>

namespace jp::console
{
   class Consolutra
   {
   public:
      Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName);

   private:
      algorithm::Properties mProperties;

      std::unique_ptr<logic::Engine> mEngine;
      std::unique_ptr<algorithm::Algorithm> mAlgorithm;
   };
}