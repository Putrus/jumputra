#include "../inc/Move.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   std::ostream& operator<<(std::ostream& os, MoveType type)
   {
      switch (type)
      {
         case MoveType::Idle:
         os << "Idle";
         break;
         case MoveType::Jump:
         os << "Jump";
         break;
         case MoveType::Run:
         os << "Run";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

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

   Move Move::random(float jumpMinY, float jumpMaxY, float runMinTime, float runMaxTime)
   {
      Move move;
      move.type = static_cast<MoveType>(core::Random::getInt(0, 1));
      if (move.type == MoveType::Jump)
      {
         move.value = core::Random::getFloat(jumpMinY, jumpMaxY);
      }
      else
      {
         move.value = core::Random::getFloat(runMinTime, runMaxTime);
      }
      move.direction = static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2));
      return move;
   }

   Move Move::randomJump(float jumpMinY, float jumpMaxY)
   {
      return Move(MoveType::Jump, static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2)),
         core::Random::getFloat(jumpMinY, jumpMaxY));
   }

   Move Move::infiniteRun(logic::CharacterDirection direction)
   {
      return Move(MoveType::Run, direction, std::numeric_limits<float>::max());
   }
}