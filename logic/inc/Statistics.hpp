#pragma once

#include "../../core/inc/Jsonable.hpp"

#include <iostream>

namespace jp::logic
{
   struct Statistics : public core::Jsonable
   {
      Statistics();
      Statistics(const nlohmann::json& json);

      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      Statistics& operator=(const nlohmann::json& json);

      int jumps = 0;
      int falls = 0;
      float time = 0.f;
      float totalTime = 0.f;
   };

   std::ostream& operator<<(std::ostream& os, const Statistics& statistics);
}