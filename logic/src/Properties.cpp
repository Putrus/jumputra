#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::logic
{
   void Properties::loadFromFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Properties::loadFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      loadFromJson(data);
   }

   void Properties::loadFromJson(const nlohmann::json& json)
   {
      secondsPerUpdate = json["logic"]["secondsPerUpdate"];

      character.jump.gain.x = json["logic"]["character"]["jump"]["gain"]["x"];
      character.jump.gain.y = json["logic"]["character"]["jump"]["gain"]["y"];
      character.jump.max.x = json["logic"]["character"]["jump"]["max"]["x"];
      character.jump.max.y = json["logic"]["character"]["jump"]["max"]["y"];
      character.runSpeed = json["logic"]["character"]["runSpeed"];

      physics.bounceFactor = json["logic"]["physics"]["bounceFactor"];
      physics.checkCollisionDistance = json["logic"]["physics"]["checkCollisionDistance"];
      physics.fallSpeed = json["logic"]["physics"]["fallSpeed"];
      physics.slipperyFriction = json["logic"]["physics"]["slipperyFriction"];
      physics.gravity.x = json["logic"]["physics"]["gravity"]["x"];
      physics.gravity.y = json["logic"]["physics"]["gravity"]["y"];
   }
}  