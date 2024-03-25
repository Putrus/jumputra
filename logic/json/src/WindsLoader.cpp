#include "../inc/WindsLoader.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game::json
{
   std::vector<std::shared_ptr<physics::Wind>> WindsLoader::loadWinds(const std::string& filename) const
   {
      std::vector<std::shared_ptr<physics::Wind>> winds;

      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::invalid_argument("WindsLoader::loadWinds - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;

      for (const auto& jsonWind : data["winds"])
      {
         math::Vector2<float> acceleration = math::Vector2<float>(jsonWind["acceleration"]["x"], jsonWind["acceleration"]["y"]);
         float impact = jsonWind["impact"];
         math::Vector2<float> maxVelocity = math::Vector2<float>(jsonWind["maxVelocity"]["x"], jsonWind["maxVelocity"]["y"]);
         math::Rect<float> rect = math::Rect<float>(jsonWind["rect"]["left"], jsonWind["rect"]["top"],
            jsonWind["rect"]["width"], jsonWind["rect"]["height"]);
         winds.push_back(std::make_shared<physics::Wind>());
      }
      return winds;
   }
}