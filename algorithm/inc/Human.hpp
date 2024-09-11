#pragma once

#include "Algorithm.hpp"

namespace jp::algorithm
{
   class Human final : public Algorithm
   {
   public:
      Human(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      std::string getName() const override;
      void update(float dt) override;
   };
}