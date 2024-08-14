#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "../../logic/inc/Character.hpp"

namespace jp::algorithm
{
   enum class MoveType : int
   {
      Jump = 0,
      Run
   };

   struct Move : public core::Jsonable
   {
      Move();
      Move(MoveType type, logic::CharacterDirection direction, float value);

      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      static Move random(float jumpMinY, float jumpMaxY, float runMinTime, float runMaxTime);
      static Move randomJump(float jumpMinY, float jumpMaxY);

      MoveType type = MoveType::Run;
      logic::CharacterDirection direction = logic::CharacterDirection::Up;
      float value = 0.f;
   };
}