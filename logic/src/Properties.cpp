#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::logic
{
   bool Properties::loadFromFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         return false;
      }

      nlohmann::json data;
      file >> data;
      file.close();

      return loadFromJson(data);
   }

   bool Properties::loadFromJson(const nlohmann::json& json)
   {
      graphic.window.size.x = json["graphic"]["window"]["size"]["x"];
      graphic.window.size.y = json["graphic"]["window"]["size"]["y"];

      logic.secondsPerUpdate = json["logic"]["secondsPerUpdate"];

      logic.character.jump.gain.x = json["logic"]["character"]["jump"]["gain"]["x"];
      logic.character.jump.gain.y = json["logic"]["character"]["jump"]["gain"]["y"];
      logic.character.jump.max.x = json["logic"]["character"]["jump"]["max"]["x"];
      logic.character.jump.max.y = json["logic"]["character"]["jump"]["max"]["y"];
      logic.character.runSpeed = json["logic"]["character"]["runSpeed"];

      logic.physics.bounceFactor = json["logic"]["physics"]["bounceFactor"];
      logic.physics.checkCollisionDistance = json["logic"]["physics"]["checkCollisionDistance"];
      logic.physics.fallSpeed = json["logic"]["physics"]["fallSpeed"];
      logic.physics.slipperyFriction = json["logic"]["physics"]["slipperyFriction"];
      logic.physics.gravity.x = json["logic"]["physics"]["gravity"]["x"];
      logic.physics.gravity.y = json["logic"]["physics"]["gravity"]["y"];

      return true;
   }
}  