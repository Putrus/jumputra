#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Greedy final : public Agent
   {
   public:
      void control(const std::shared_ptr<logic::Engine>& engine) override;

      bool o = true;
   };
}