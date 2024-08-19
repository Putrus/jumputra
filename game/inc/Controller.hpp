#pragma once

#include <iostream>

namespace jp::game
{
   enum class Controller
   {
      AntColony = 0,
      DecisionTree,
      Genetic,
      Greedy,
      Human
   };

   std::ostream& operator<<(std::ostream& os, Controller controller);
}