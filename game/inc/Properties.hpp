#pragma once

#include "../../graphic/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      graphic::Properties graphic;
      logic::Properties logic;
   };
}