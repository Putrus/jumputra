#pragma once

#include "Wind.hpp"

namespace jp::game::physics
{
   class WindUpdater final
   {
   public:
      void update(float dt, Wind& wind) const;
   };
}