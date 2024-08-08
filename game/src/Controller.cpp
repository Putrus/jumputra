#include "../inc/Controller.hpp"

namespace jp::game
{
   std::ostream& operator<<(std::ostream& os, Controller controller)
   {
      switch (controller)
      {
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