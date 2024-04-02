#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::game
{
   void Properties::loadFromFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::game::Properties::loadFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      loadFromJson(data);
   }

   void Properties::loadFromJson(const nlohmann::json& json)
   {
      graphic.loadFromJson(json);
      logic.loadFromJson(json);
   }
}