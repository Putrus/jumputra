#pragma once

#include "Loadable.hpp"

#include <iostream>

namespace jp::logic
{
   struct Statistics : public Loadable
   {
      Statistics();
      Statistics(const nlohmann::json& json);
      void loadFromJson(const nlohmann::json& json) override;

      int jumps = 0;
      int falls = 0;
      float time = 0.f;
   };

   std::ostream &operator<<(std::ostream &os, const Statistics &statistics);
}