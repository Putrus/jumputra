#include "../inc/WindsLoader.hpp"

#include <fstream>

namespace jp::logic
{
   std::vector<std::shared_ptr<Wind>> WindsLoader::loadWindsFromFile(const std::string &filename) const
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::WindsLoader::loadWindsFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      return loadWindsFromJson(data);
   }

   std::vector<std::shared_ptr<Wind>> WindsLoader::loadWindsFromJson(const nlohmann::json& json) const
   {
      std::vector<std::shared_ptr<Wind>> winds;
      for (const auto& jsonWind : json["winds"])
      {
         float impact = jsonWind["impact"];
         math::Vector2<float> acceleration(jsonWind["acceleration"]["x"], jsonWind["acceleration"]["y"]);
         math::Vector2<float> maxVelocity(jsonWind["maxVelocity"]["x"], jsonWind["maxVelocity"]["y"]);
         math::Rect<float> rect(jsonWind["rect"]["left"], jsonWind["rect"]["top"],
               jsonWind["rect"]["width"], jsonWind["rect"]["height"]);
         winds.push_back(std::make_shared<Wind>(impact, maxVelocity, rect, acceleration));
      }

      return winds;
   }
}