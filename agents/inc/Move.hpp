#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "../../logic/inc/Character.hpp"

namespace jp::agents
{
   enum class MoveType : int
   {
      Jump = 0,
      Run
   };

   struct Move : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;
      
      MoveType type;
      logic::CharacterDirection direction;
      float value;
   };
}