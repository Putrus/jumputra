#pragma once

#include "../../algorithm/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::console
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      algorithm::Properties algorithm;
      logic::Properties logic;
   };
}