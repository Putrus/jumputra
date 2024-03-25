#include "../inc/PropertiesLoader.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game::json
{
   Properties PropertiesLoader::loadProperties(const std::string& filename) const
   {
      Properties properties;

      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::invalid_argument("PropertiesLoader::loadProperties - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;

      properties.logic.secondsPerFrame = data["logic"]["secondsPerFrame"];
      properties.physics.bounceFactor = data["physics"]["bounceFactor"];
      properties.physics.checkCollisionDistance = data["physics"]["checkCollisionDistance"];
      properties.physics.fallSpeed = data["physics"]["fallSpeed"];
      properties.physics.slipperyFriction = data["physics"]["slipperyFriction"];
      properties.physics.gravity.x = data["physics"]["gravity"]["x"];
      properties.physics.gravity.y = data["physics"]["gravity"]["y"];

      file.close();

      return properties;
   }
}