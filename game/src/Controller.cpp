#include "../inc/Controller.hpp"

namespace jp::game
{
   std::ostream& operator<<(std::ostream& os, Controller controller)
   {
      switch (controller)
      {
         case Controller::AntColony:
         os << "AntColony";
         break;
         case Controller::DecisionTree:
         os << "DecisionTree";
         break;
         case Controller::Genetic:
         os << "Genetic";
         break;
         case Controller::Greedy:
         os << "Greedy";
         break;
         case Controller::Human:
         os << "Human";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }
}