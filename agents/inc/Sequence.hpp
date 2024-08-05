#pragma once

#include "Agent.hpp"

namespace jp::agents
{
   class Sequence final : public Agent
   {
   public:
      Sequence(const std::shared_ptr<logic::Engine>& engine);

      void update(float dt) override;
   };
}