#pragma once

#include <iostream>

namespace jp::logic
{
   struct Statistics
   {
      int jumps = 0;
      int falls = 0;
      float time = 0.f;
   };

   std::ostream &operator<<(std::ostream &os, const Statistics &statistics);
}