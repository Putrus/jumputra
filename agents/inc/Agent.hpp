#pragma once

#include "../../logic/inc/Engine.hpp"

namespace jp::agents
{
   enum class AgentName : int
   {
      Greedy = 0,
      Human
   };

   std::ostream& operator<<(std::ostream& os, AgentName name);

   class Agent
   {
   public:
      virtual void control(const std::shared_ptr<logic::Engine>& engine) = 0;

      static std::unique_ptr<Agent> create(AgentName name);
   };
}