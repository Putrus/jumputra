#pragma once

#include "../../core/inc/Jsonable.hpp"

namespace jp::agents
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      struct Greedy
      {
         size_t bots;
      } greedy;
   };
}