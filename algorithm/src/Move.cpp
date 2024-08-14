#include "../inc/Move.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Move::Move() {}
   
   Move::Move(MoveType type, logic::CharacterDirection direction, float value)
      : type(type), direction(direction), value(value) {}

   void Move::fromJson(const nlohmann::json& json)
   {
      type = json.at("move");
      direction = static_cast<logic::CharacterDirection>(json.at("direction"));
      value = json.at("value");
   }

   nlohmann::json Move::toJson() const
   {
      nlohmann::json json;
      json["type"] = type;
      json["direction"] = static_cast<int>(direction);
      json["value"] = value;
      return json;
   }

   Move Move::random(float jumpMaxY, float runMaxTime)
   {
      Move move;
      move.type = static_cast<MoveType>(core::Random::getInt(0, 1));
      if (move.type == MoveType::Jump)
      {
         move.value = core::Random::getFloat(1.f, jumpMaxY);
      }
      else
      {
         move.value = core::Random::getFloat(0.1f, runMaxTime);
      }
      move.direction = static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2));
      return move;
   }

   Move Move::randomJump(float jumpMaxY)
   {
      return Move(MoveType::Jump, static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2)),
         core::Random::getFloat(0.f, jumpMaxY));
   }
}