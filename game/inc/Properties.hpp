#pragma once

#include "../../agents/inc/Properties.hpp"
#include "../../graphic/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      agents::Properties agents;
      graphic::Properties graphic;
      logic::Properties logic;
   };
}