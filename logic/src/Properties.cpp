#include "../inc/Properties.hpp"

#include <fstream>

namespace jp::logic
{
   void Properties::fromJson(const nlohmann::json& json)
   {
      secondsPerUpdate = json.at("secondsPerUpdate");

      character.jump.gain.x = json.at("character").at("jump").at("gain").at("x");
      character.jump.gain.y = json.at("character").at("jump").at("gain").at("y");
      character.jump.max.x = json.at("character").at("jump").at("max").at("x");
      character.jump.max.y = json.at("character").at("jump").at("max").at("y");
      character.runSpeed = json.at("character").at("runSpeed");
      character.size.x = json.at("character").at("size").at("x");
      character.size.y = json.at("character").at("size").at("y");

      physics.bounceFactor = json.at("physics").at("bounceFactor");
      physics.checkCollisionDistance = json.at("physics").at("checkCollisionDistance");
      physics.fallSpeed = json.at("physics").at("fallSpeed");
      physics.slipperyFriction = json.at("physics").at("slipperyFriction");
      physics.gravity.x = json.at("physics").at("gravity").at("x");
      physics.gravity.y = json.at("physics").at("gravity").at("y");
   }

   nlohmann::json Properties::toJson() const
   {
      nlohmann::json json;
      json.at("secondsPerUpdate") = secondsPerUpdate;

      json.at("character").at("jump").at("gain").at("x") = character.jump.gain.x;
      json.at("character").at("jump").at("gain").at("y") = character.jump.gain.y;
      json.at("character").at("jump").at("max").at("x") = character.jump.max.x;
      json.at("character").at("jump").at("max").at("y") = character.jump.max.y;
      json.at("character").at("runSpeed") = character.runSpeed;
      json.at("character").at("size").at("x") = character.size.x;
      json.at("character").at("size").at("y") = character.size.y;

      json.at("physics").at("bounceFactor") = physics.bounceFactor;
      json.at("physics").at("checkCollisionDistance") = physics.checkCollisionDistance;
      json.at("physics").at("fallSpeed") = physics.fallSpeed;
      json.at("physics").at("slipperyFriction") = physics.slipperyFriction;
      json.at("physics").at("gravity").at("x") = physics.gravity.x;
      json.at("physics").at("gravity").at("y") = physics.gravity.y;

      return json;
   }
}  