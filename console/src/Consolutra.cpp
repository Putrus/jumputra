#include "../inc/Consolutra.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::console
{
   Consolutra::Consolutra(const std::string& propertiesFilename, const std::string& worldFilename, const std::string& algorithmName)
   {
      mEngine->loadFromJsonFile(worldFilename);
   }
}