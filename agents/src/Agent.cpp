#include "../inc/Agent.hpp"
#include "../inc/Greedy.hpp"
#include "../inc/Human.hpp"
namespace jp::agents
{
   std::ostream& operator<<(std::ostream& os, AgentName name)
   {
      switch (name)
      {
         case AgentName::Human:
         os << "Human";
         break;
         case AgentName::Greedy:
         os << "Greedy";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   std::unique_ptr<Agent> Agent::create(AgentName name)
   {
      switch (name)
      {
      case AgentName::Greedy:
         return std::make_unique<Greedy>();
      case AgentName::Human:
         return std::make_unique<Human>();
      default:
         return nullptr;
      }
   }
}