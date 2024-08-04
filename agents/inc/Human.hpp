#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Human final : public Agent
   {
   public:
      void control(const std::shared_ptr<logic::Engine>& engine) override;
   };
}