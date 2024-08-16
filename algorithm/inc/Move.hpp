#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "../../logic/inc/Character.hpp"

namespace jp::algorithm
{
   enum class MoveType : int
   {
      Idle = 0,
      Jump,
      Run
   };

   std::ostream& operator<<(std::ostream& os, MoveType type);

   struct Move : public core::Jsonable
   {
      Move();
      Move(MoveType type, logic::CharacterDirection direction, float value);

      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      static Move random(float jumpMinY, float jumpMaxY, float runMinTime, float runMaxTime);
      static Move randomJump(float jumpMinY, float jumpMaxY);
      static Move infiniteRun(logic::CharacterDirection direction);

      MoveType type = MoveType::Idle;
      logic::CharacterDirection direction = logic::CharacterDirection::Up;
      float value = 0.f;
   };
}