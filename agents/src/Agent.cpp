#include "../inc/Agent.hpp"
#include "../inc/Greedy.hpp"
#include "../inc/Human.hpp"

#include <fstream>

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

   Agent::Agent(const std::shared_ptr<logic::Engine>& engine) : mEngine(engine) {}

   void Agent::saveMoves(const std::string &filename) const
   {
      nlohmann::json json;
      for (const auto& move : mMoves)
      {
         json["moves"].push_back(move.toJson());
      }
      std::ofstream file(filename);
      file << json;
      file.close();
   }
}