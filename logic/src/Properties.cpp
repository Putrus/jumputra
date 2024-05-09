#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::logic
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      secondsPerUpdate = json["secondsPerUpdate"];

      character.jump.gain.x = json["character"]["jump"]["gain"]["x"];
      character.jump.gain.y = json["character"]["jump"]["gain"]["y"];
      character.jump.max.x = json["character"]["jump"]["max"]["x"];
      character.jump.max.y = json["character"]["jump"]["max"]["y"];
      character.runSpeed = json["character"]["runSpeed"];
      character.size.x = json["character"]["size"]["x"];
      character.size.y = json["character"]["size"]["y"];

      physics.bounceFactor = json["physics"]["bounceFactor"];
      physics.checkCollisionDistance = json["physics"]["checkCollisionDistance"];
      physics.fallSpeed = json["physics"]["fallSpeed"];
      physics.slipperyFriction = json["physics"]["slipperyFriction"];
      physics.gravity.x = json["physics"]["gravity"]["x"];
      physics.gravity.y = json["physics"]["gravity"]["y"];
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json["secondsPerUpdate"] = secondsPerUpdate;

      json["character"]["jump"]["gain"]["x"] = character.jump.gain.x;
      json["character"]["jump"]["gain"]["y"] = character.jump.gain.y;
      json["character"]["jump"]["max"]["x"] = character.jump.max.x;
      json["character"]["jump"]["max"]["y"] = character.jump.max.y;
      json["character"]["runSpeed"] = character.runSpeed;
      json["character"]["size"]["x"] = character.size.x;
      json["character"]["size"]["y"] = character.size.y;

      json["physics"]["bounceFactor"] = physics.bounceFactor;
      json["physics"]["checkCollisionDistance"] = physics.checkCollisionDistance;
      json["physics"]["fallSpeed"] = physics.fallSpeed;
      json["physics"]["slipperyFriction"] = physics.slipperyFriction;
      json["physics"]["gravity"]["x"] = physics.gravity.x;
      json["physics"]["gravity"]["y"] = physics.gravity.y;

      return json;
   }
}  