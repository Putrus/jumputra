#pragma once

#include "../../algorithm/inc/Properties.hpp"
#include "../../graphic/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      algorithm::Properties algorithm;
      graphic::Properties graphic;
      logic::Properties logic;
   };
}