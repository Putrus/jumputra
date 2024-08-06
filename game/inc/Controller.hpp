#pragma once

#include <iostream>

namespace jp::game
{
   enum class Controller
   {
      Genetic = 0,
      Greedy,
      Human,
      Sequence
   };

   std::ostream& operator<<(std::ostream& os, Controller controller);
}